//VTK::System::Dec

/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkPolyDataVS.glsl

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

attribute vec4 vertexDC;

varying vec3 vertexVCVSOutput;
uniform mat4 PCVCMatrix;

uniform float dcxmin;
uniform float dcxmax;
uniform float dcymin;
uniform float dcymax;

varying vec3 vertexDCOutput;
varying vec3 vertexDCAllOutput;
void main()
{
  // dcsmall is the device coords reduced to the
  // x y area covered by the volume
  vec4 dcsmall = vec4(
    dcxmin + 0.5 * (vertexDC.x + 1.0) * (dcxmax - dcxmin),
    dcymin + 0.5 * (vertexDC.y + 1.0) * (dcymax - dcymin),
    vertexDC.z,
    vertexDC.w);
  vec4 vcpos = PCVCMatrix * dcsmall;
  vertexVCVSOutput = vcpos.xyz/vcpos.w;
  vertexDCOutput = vertexDC.xyz;
  vertexDCAllOutput = dcsmall.xyz;
  gl_Position = dcsmall;
}
