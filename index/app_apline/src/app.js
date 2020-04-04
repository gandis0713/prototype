var app = {
  spline: {
    data: {    
      input: [[100, 200, 200, 100], [100, 100, 200, 200]],
      output: [[[]]]
    },
    spec: {
      close: true,
      resolution: 32,
      intervals: [0, 0.25, 0.5, 0.75, 1],
    
      tension: [0, 0, 0, 0],
      bias: [0, 0, 0, 0],
      continuity: [0, 0, 0, 0]
    }
  },
  state: {
    isDragging: false,
    selectedIndex: -1
  }
}

const splineType = [[0, '#ff0000', 'kochanek'], [1, '#0000ff', 'natural']];

function App(rootElementName) {

  this.splineController = null;

  this.start = function() {

    this.splineController = new SplineController();
    this.splineController.setScreen(new SplineScreen(rootElementName, this.splines));
    this.splineController.setPanel(new SplinePanel(rootElementName));
  }

}