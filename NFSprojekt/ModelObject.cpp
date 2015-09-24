#include "ModelObject.h"

void ModelObject::createArrayBuffer()		//Dodawanie wierzcholka do pamieci OpenGl
{
	GLuint  vertexLoc = 0, normalLoc = 1, texCoordLoc = 2;

	GLuint VAid;
	glGenVertexArrays(1, &VAid);
	glBindVertexArray(VAid);

	GLuint *generatedIndices = new GLuint[sizeof(GLuint) * this->verticesCount * 3];
	for (int i = 0; i<sizeof(GLuint) * this->verticesCount * 3; i++)
		generatedIndices[i] = i;

	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * verticesCount * 3, generatedIndices, GL_STATIC_DRAW);

	if (this->v && this->verticesCount > 0) {
		glGenBuffers(1, &buffer);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * this->verticesCount, this->v, GL_STATIC_DRAW);
		glEnableVertexAttribArray(vertexLoc);
		glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}
	if (this->n && this->verticesCount > 0) {
		glGenBuffers(1, &buffer);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * this->verticesCount, this->n, GL_STATIC_DRAW);
		glEnableVertexAttribArray(normalLoc);
		glVertexAttribPointer(normalLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}

	if (this->uv && this->verticesCount > 0) {
		glGenBuffers(1, &buffer);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * this->verticesCount, this->uv, GL_STATIC_DRAW);
		glEnableVertexAttribArray(texCoordLoc);
		glVertexAttribPointer(texCoordLoc, 2, GL_FLOAT, GL_FALSE, 0, 0);
	}

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	this->arrayBuffer = VAid;
}

void ModelObject::extractMesh(FbxNode* node){
	FbxMesh* pMesh = node->GetMesh();
	FbxVector4* pVertices = pMesh->GetControlPoints();
	FbxLayerElementArrayTemplate<FbxVector2>* uvVertices = 0;
	pMesh->GetTextureUV(&uvVertices, FbxLayerElement::eTextureDiffuse);

	FbxLayerElementArrayTemplate<FbxVector4>* normalsArr = 0;
	pMesh->GetNormals(&normalsArr);

	FbxLayerElementArrayTemplate<FbxVector4>* tangentArr = 0;
	pMesh->GetTangents(&tangentArr);

	this->v = new GLfloat[pMesh->GetPolygonCount() * 9];
	this->uv = new GLfloat[pMesh->GetPolygonCount() * 6];
	this->n = new GLfloat[pMesh->GetPolygonCount() * 9];

	int vi = 0,
		uvi = 0,
		ni = 0;
	this->verticesCount = 0;
	for (int j = 0; j < pMesh->GetPolygonCount(); j++)
	{
		int iNumVertices = pMesh->GetPolygonSize(j);
		if (iNumVertices != 3);// ERROR("Model is not triangulated!");

		for (int k = 0; k < iNumVertices; k++)
		{
			FbxVector4 fbxNorm(0, 0, 0, 0);
			int iControlPointIndex = pMesh->GetPolygonVertex(j, k);
			int iTextureUVIndex = pMesh->GetTextureUVIndex(j, k);

			pMesh->GetPolygonVertexNormal(j, k, fbxNorm);

			this->v[vi++] = (pVertices[iControlPointIndex].mData[0]);
			this->v[vi++] = (pVertices[iControlPointIndex].mData[1]);
			this->v[vi++] = (pVertices[iControlPointIndex].mData[2]);
			this->uv[uvi++] = ((*uvVertices)[iTextureUVIndex][0]);
			this->uv[uvi++] = ((*uvVertices)[iTextureUVIndex][1]);
			this->n[ni++] = (fbxNorm[0]);
			this->n[ni++] = (fbxNorm[1]);
			this->n[ni++] = (fbxNorm[2]);

			this->verticesCount++;
		}
	}
}

ModelObject::ModelObject(FbxNode* node)
{
	this->name = node->GetName();

	this->diffuseMap = new Texture((std::string(TEXTURES_SUBDIR) + std::string(this->name) + "_COLOR.png").c_str());	//pobranie tekstury

	FbxDouble3 pos = node->LclTranslation.Get();	//pozycja podobiektu
	this->relativePosition.x = pos.mData[0];
	this->relativePosition.y = pos.mData[1];
	this->relativePosition.z = pos.mData[2];

	this->extractMesh(node);	//pobieranie siatki
	this->createArrayBuffer();
}

ModelObject::~ModelObject()
{
}