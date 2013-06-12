xof 0303txt 0032
template Header {
 <3d82ab43-62da-11cf-ab39-0020af71e433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3d82ab5e-62da-11cf-ab39-0020af71e433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <f6f23f44-7686-11cf-8f52-0040333594a3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <f6f23f45-7686-11cf-8f52-0040333594a3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35ff44e0-6c7c-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <d3e16e81-7835-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630b820-7842-11cf-8f52-0040333594a3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <537da6a0-ca37-11d0-941c-0080c80cfa7b>
 DWORD truefalse;
}

template Boolean2d {
 <4885ae63-78e8-11cf-8f52-0040333594a3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885ae60-78e8-11cf-8f52-0040333594a3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <a42790e1-7810-11cf-8f52-0040333594a3>
 STRING filename;
}

template Material {
 <3d82ab4d-62da-11cf-ab39-0020af71e433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3d82ab5f-62da-11cf-ab39-0020af71e433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <ed1ec5c0-c0a8-11d0-941c-0080c80cfa7b>
 DWORD nFaceWrapValues;
 array Boolean2d faceWrapValues[nFaceWrapValues];
}

template MeshTextureCoords {
 <f6f23f40-7686-11cf-8f52-0040333594a3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <f6f23f42-7686-11cf-8f52-0040333594a3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material <3d82ab4d-62da-11cf-ab39-0020af71e433>]
}

template MeshNormals {
 <f6f23f43-7686-11cf-8f52-0040333594a3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630b821-7842-11cf-8f52-0040333594a3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3d82ab44-62da-11cf-ab39-0020af71e433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}


Header {
 1;
 0;
 1;
}

Mesh {
 24;
 -2.500000;2.500000;-2.500000;,
 -2.500000;2.500000;-2.500000;,
 -2.500000;2.500000;-2.500000;,
 -2.500000;2.500000;2.500000;,
 -2.500000;2.500000;2.500000;,
 -2.500000;2.500000;2.500000;,
 -2.500000;-2.500000;2.500000;,
 -2.500000;-2.500000;2.500000;,
 -2.500000;-2.500000;2.500000;,
 -2.500000;-2.500000;-2.500000;,
 -2.500000;-2.500000;-2.500000;,
 -2.500000;-2.500000;-2.500000;,
 2.500000;2.500000;2.500000;,
 2.500000;2.500000;2.500000;,
 2.500000;2.500000;2.500000;,
 2.500000;-2.500000;2.500000;,
 2.500000;-2.500000;2.500000;,
 2.500000;-2.500000;2.500000;,
 2.500000;2.500000;-2.500000;,
 2.500000;2.500000;-2.500000;,
 2.500000;2.500000;-2.500000;,
 2.500000;-2.500000;-2.500000;,
 2.500000;-2.500000;-2.500000;,
 2.500000;-2.500000;-2.500000;;
 12;
 3;2,8,5;,
 3;11,8,2;,
 3;4,17,14;,
 3;7,17,4;,
 3;13,23,20;,
 3;16,23,13;,
 3;19,10,1;,
 3;22,10,19;,
 3;9,15,6;,
 3;21,15,9;,
 3;18,3,12;,
 3;0,3,18;;

 MeshMaterialList {
  1;
  1;
  0;

  Material {
   1.000000;1.000000;1.000000;1.000000;;
   31.799999;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
  }
 }

 MeshNormals {
  24;
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;-1.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;;
  12;
  3;2,8,5;,
  3;11,8,2;,
  3;4,17,14;,
  3;7,17,4;,
  3;13,23,20;,
  3;16,23,13;,
  3;19,10,1;,
  3;22,10,19;,
  3;9,15,6;,
  3;21,15,9;,
  3;18,3,12;,
  3;0,3,18;;
 }

 MeshTextureCoords {
  24;
  0.000611;0.330981;,
  -0.002140;0.667197;,
  0.500915;0.333577;,
  0.000611;-0.000510;,
  0.998753;0.669414;,
  0.002159;0.333577;,
  0.503577;0.329579;,
  0.998752;0.999913;,
  0.002159;0.666081;,
  0.503577;0.000867;,
  -0.002140;1.000417;,
  0.500915;0.666081;,
  0.497848;-0.000510;,
  0.998986;0.334332;,
  0.503004;0.669414;,
  0.996644;0.329579;,
  0.998986;0.665370;,
  0.503004;0.999913;,
  0.497848;0.330981;,
  0.497690;0.667197;,
  0.502428;0.334332;,
  0.996644;0.000868;,
  0.497690;1.000417;,
  0.502428;0.665370;;
 }
}