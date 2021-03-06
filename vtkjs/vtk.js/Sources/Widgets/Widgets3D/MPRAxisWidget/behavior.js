import { vec3, mat4 } from 'gl-matrix';

import macro from 'vtk.js/Sources/macro';
import vtkBoundingBox from 'vtk.js/Sources/Common/DataModel/BoundingBox';
import vtkLine from 'vtk.js/Sources/Common/DataModel/Line';
import vtkPlaneManipulator from 'vtk.js/Sources/Widgets/Manipulators/PlaneManipulator';
import * as vtkMath from 'vtk.js/Sources/Common/Core/Math';

import {
  boundPointOnPlane,
  getAssociatedLinesName,
  updateState,
  getViewPlaneNameFromViewType
} from './helpers';

export default function widgetBehavior(publicAPI, model) {
  let isDragging = null;
  let preWorldCoords = [0, 0, 0];
  let curWorldCoords = [0, 0, 0];

  function getWorldCoords(callData) {
    const viewType = callData.pokedRenderer.getViewType();
    const viewName = getViewPlaneNameFromViewType(viewType);
    const currentPlaneNormal = model.widgetState[`get${viewName}PlaneNormal`]();
    model.planeManipulator.setOrigin(model.widgetState.getCenter());
    model.planeManipulator.setNormal(currentPlaneNormal);
    const worldCoords = model.planeManipulator.handleEvent(callData, model.openGLRenderWindow);
    return worldCoords;
  }

  publicAPI.updateCursor = () => {
    const center = model.widgetState.getCenter();
    const length = vec3.distance(center, curWorldCoords);
    const axisGuidePosFromCenter = model.widgetState.getAxisGuidePosFromCenter();
    const rotateGuidePosFromCenter = model.widgetState.getRotateGuidePosFromCenter();
    if (length < axisGuidePosFromCenter) {
      model.widgetState.setUpdateMethodName('translateCenter');
      model.openGLRenderWindow.setCursor('move');
    } else if (length >= axisGuidePosFromCenter && length < rotateGuidePosFromCenter) {
      model.widgetState.setUpdateMethodName('translateAxis');
      model.openGLRenderWindow.setCursor('pointer');
    } else {
      model.widgetState.setUpdateMethodName('rotateLine');
      model.openGLRenderWindow.setCursor('alias');
    }
  };

  publicAPI.handleLeftButtonPress = callData => {
    const { pokedRenderer } = callData;
    if (pokedRenderer !== model.renderer) {
      return macro.VOID;
    }

    let returnValue = macro.EVENT_ABORT;
    if (model.activeState && model.activeState.getActive()) {
      isDragging = true;
      const viewName = model.widgetState.getActiveViewName();
      const currentPlaneNormal = model.widgetState[`get${viewName}PlaneNormal`]();
      model.planeManipulator.setOrigin(model.widgetState.getCenter());
      model.planeManipulator.setNormal(currentPlaneNormal);

      publicAPI.startInteraction();
      returnValue = macro.EVENT_ABORT;
    } else {
      returnValue = macro.VOID;
    }

    preWorldCoords = model.planeManipulator.handleEvent(callData, model.openGLRenderWindow);
    return returnValue;
  };

  publicAPI.handleMouseMove = callData => {
    const { pokedRenderer } = callData;
    if (pokedRenderer !== model.renderer) {
      return macro.VOID;
    }

    let returnValue = macro.VOID;
    curWorldCoords = getWorldCoords(callData);

    if (isDragging && model.pickable) {
      returnValue = publicAPI.handleEvent(callData);
    }

    preWorldCoords = curWorldCoords;
    return returnValue;
  };

  publicAPI.handleLeftButtonRelease = callData => {
    if (callData.pokedRenderer !== model.renderer) {
      return macro.VOID;
    }
    if (isDragging) {
      publicAPI.endInteraction();
    }
    isDragging = false;
    model.widgetState.deactivate();
  };

  publicAPI.handleRightButtonPress = callData => {};

  publicAPI.handleRightButtonRelease = callData => {};

  publicAPI.handleStartMouseWheel = callData => {
    if (callData.pokedRenderer !== model.renderer) {
      return macro.VOID;
    }
    publicAPI.startInteraction();
    return macro.EVENT_ABORT;
  };

  publicAPI.handleMouseWheel = callData => {
    if (callData.pokedRenderer !== model.renderer) {
      return macro.VOID;
    }
    const step = callData.spinY;
    publicAPI.translateCenterOnCurrentDirection(step, callData.pokedRenderer);

    publicAPI.invokeInteractionEvent();

    return macro.EVENT_ABORT;
  };

  publicAPI.handleEndMouseWheel = callData => {
    if (callData.pokedRenderer !== model.renderer) {
      return macro.VOID;
    }
    publicAPI.endInteraction();
    return macro.EVENT_ABORT;
  };

  publicAPI.handleMiddleButtonPress = () => {};

  publicAPI.handleMiddleButtonRelease = () => {};

  publicAPI.handleEvent = callData => {
    let returnValue = macro.VOID;

    if (model.activeState.getActive()) {
      publicAPI[model.activeState.getUpdateMethodName()](callData);
      publicAPI.invokeInteractionEvent();

      returnValue = macro.EVENT_ABORT;
    }

    return returnValue;
  };

  publicAPI.startInteraction = () => {
    publicAPI.invokeStartInteractionEvent();
    // When interacting, plane actor and lines must be re-rendered on other views
    publicAPI.getViewWidgets().forEach(viewWidget => {
      const interactor = viewWidget.getInteractor();
      if (!interactor.isRequestedAnimation(publicAPI)) {
        viewWidget.getInteractor().requestAnimation(publicAPI);
      }
    });
  };

  publicAPI.endInteraction = () => {
    publicAPI.invokeEndInteractionEvent();
    publicAPI.getViewWidgets().forEach(viewWidget => {
      const interactor = viewWidget.getInteractor();
      if (interactor.isRequestedAnimation(publicAPI)) {
        viewWidget.getInteractor().cancelAnimation(publicAPI);
      }
    });
  };

  publicAPI.translateCenterOnCurrentDirection = (nbSteps, renderer) => {
    const dirProj = renderer
      .getRenderWindow()
      .getRenderers()[0]
      .getActiveCamera()
      .getDirectionOfProjection();

    // Direction of the projection is the inverse of what we want
    const direction = vtkMath.multiplyScalar(dirProj, -1);

    const oldCenter = model.widgetState.getCenter();
    const image = model.widgetState.getImage();
    const imageSpacing = image.getSpacing();

    // Define the potentially new center
    let newCenter = [
      oldCenter[0] + nbSteps * direction[0] * imageSpacing[0],
      oldCenter[1] + nbSteps * direction[1] * imageSpacing[1],
      oldCenter[2] + nbSteps * direction[2] * imageSpacing[2]
    ];
    newCenter = publicAPI.getBoundedCenter(newCenter);

    model.widgetState.setCenter(newCenter);
    updateState(model.widgetState);
  };

  publicAPI.translateAxis = callData => {
    const stateLine = model.widgetState.getActiveLineState();
    const worldCoords = model.planeManipulator.handleEvent(callData, model.openGLRenderWindow);

    const point1 = stateLine.getPoint1();
    const point2 = stateLine.getPoint2();

    // Translate the current line along the other line
    const otherLineName = getAssociatedLinesName(stateLine.getName());
    const otherLine = model.widgetState[`get${otherLineName}`]();
    const otherLineVector = vtkMath.subtract(otherLine.getPoint2(), otherLine.getPoint1(), []);
    vtkMath.normalize(otherLineVector);
    const axisTranslation = otherLineVector;

    const currentLineVector = vtkMath.subtract(point2, point1, [0, 0, 0]);
    vtkMath.normalize(currentLineVector);

    const dot = vtkMath.dot(currentLineVector, otherLineVector);
    // lines are colinear, translate along perpendicular axis from current line
    if (dot === 1 || dot === -1) {
      vtkMath.cross(currentLineVector, model.planeManipulator.getNormal(), axisTranslation);
    }

    const closestPoint = [];
    vtkLine.distanceToLine(worldCoords, point1, point2, closestPoint);

    const translationVector = vtkMath.subtract(worldCoords, closestPoint, []);
    const translationDistance = vtkMath.dot(translationVector, axisTranslation);

    const center = model.widgetState.getCenter();
    let newOrigin = vtkMath.multiplyAccumulate(center, axisTranslation, translationDistance, [
      0,
      0,
      0
    ]);
    newOrigin = publicAPI.getBoundedCenter(newOrigin);
    model.widgetState.setCenter(newOrigin);
    updateState(model.widgetState);
  };

  publicAPI.getBoundedCenter = newCenter => {
    const oldCenter = model.widgetState.getCenter();
    const imageBounds = model.widgetState.getImage().getBounds();
    const bounds = vtkBoundingBox.newInstance({ bounds: imageBounds });

    if (bounds.containsPoint(...newCenter)) {
      return newCenter;
    }

    return boundPointOnPlane(newCenter, oldCenter, imageBounds);
  };

  publicAPI.translateCenter = callData => {
    const { pokedRenderer } = callData;
    const curWorldCoords = model.planeManipulator.handleEvent(callData, model.openGLRenderWindow);
    const center = model.widgetState.getCenter();
    const preWCToCurWC = [0, 0, 0];
    vec3.subtract(preWCToCurWC, curWorldCoords, preWorldCoords);
    let newCenter = [
      center[0] + preWCToCurWC[0],
      center[1] + preWCToCurWC[1],
      center[2] + preWCToCurWC[2]
    ];

    if (model.widgetState.getKeepInVolume()) {
      newCenter = publicAPI.getBoundedCenter(newCenter);
    }
    model.activeState.setCenter(newCenter);
    updateState(model.widgetState);
  };

  publicAPI.rotateLine = callData => {
    const activeLine = model.widgetState.getActiveLineState();
    const planeNormal = model.planeManipulator.getNormal();
    const worldCoords = model.planeManipulator.handleEvent(callData, model.openGLRenderWindow);
    const center = model.widgetState.getCenter();
    const previousWorldPosition = preWorldCoords;
    const previousVectorToOrigin = [0, 0, 0];
    vtkMath.subtract(previousWorldPosition, center, previousVectorToOrigin);
    vtkMath.normalize(previousVectorToOrigin);
    const currentVectorToOrigin = [0, 0, 0];
    vtkMath.subtract(worldCoords, center, currentVectorToOrigin);
    vtkMath.normalize(currentVectorToOrigin);
    const rotationAngle = vtkMath.angleBetweenVectors(
      previousVectorToOrigin,
      currentVectorToOrigin
    );
    // Define the direction of the rotation
    const cross = [0, 0, 0];
    vtkMath.cross(currentVectorToOrigin, previousVectorToOrigin, cross);
    vtkMath.normalize(cross);
    const sign = vtkMath.dot(cross, planeNormal) > 0 ? -1 : 1;
    const matrix = mat4.create();
    mat4.translate(matrix, matrix, center);
    mat4.rotate(matrix, matrix, rotationAngle * sign, planeNormal);
    mat4.translate(matrix, matrix, [-center[0], -center[1], -center[2]]);
    // Rotate associated line's plane normal
    const planeName = activeLine.getPlaneName();
    const normal = model.widgetState[`get${planeName}PlaneNormal`]();
    const newNormal = vtkMath.rotateVector(normal, planeNormal, rotationAngle * sign);
    model.widgetState[`set${planeName}PlaneNormal`](newNormal);
    if (model.widgetState.getKeepOrthogonality()) {
      const associatedLineName = getAssociatedLinesName(activeLine.getName());
      const associatedLine = model.widgetState[`get${associatedLineName}`]();
      const planeName2 = associatedLine.getPlaneName();
      const normal2 = model.widgetState[`get${planeName2}PlaneNormal`]();
      const newNormal2 = vtkMath.rotateVector(normal2, planeNormal, rotationAngle * sign);
      model.widgetState[`set${planeName2}PlaneNormal`](newNormal2);
    }
    updateState(model.widgetState);
  };

  // --------------------------------------------------------------------------
  // initialization
  // --------------------------------------------------------------------------

  model.planeManipulator = vtkPlaneManipulator.newInstance();
}
