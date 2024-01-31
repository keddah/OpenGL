#include "Model.h"

Model::Model(Camera& cam)
{
	Assimp::Importer importer;
	const aiScene* scene = 
	importer.ReadFile
	(
		filePath,
		aiProcess_CalcTangentSpace | 
		aiProcess_Triangulate | 
		aiProcess_JoinIdenticalVertices | 
		aiProcess_SortByPType
		//aiProcess_FlipUVs
	);

	if (!scene)
	{
		print("Couldn't import model")
		return;
	}


	for (int i = 0; i < scene->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[i];
		vector<GLfloat> vertices;
		vector<GLuint> indices;

		for (int j = 0; j < mesh->mNumVertices; j++) {

			// Pushing the position
			const aiVector3D* pos = &mesh->mVertices[j];
			vertices.push_back(pos->x);
			vertices.push_back(pos->y);
			vertices.push_back(pos->z);

			// Pushing the colour
			vertices.push_back(.4f + j * .001f);
			vertices.push_back(.1f + j * .001f);
			vertices.push_back(.3f + j * .001f);
			vertices.push_back(1);

			// Pushing the tex coords
			// Check if there are any present
			if (!mesh->HasTextureCoords(0)) continue;

			vertices.push_back(mesh->mTextureCoords[0][i].x); 
			vertices.push_back(mesh->mTextureCoords[0][i].y);
		}

		for (int j = 0; j < mesh->mNumFaces; j++) {
			aiFace* f = &mesh->mFaces[j];
			if (f->mNumIndices != 3) {
				//only load triangluar faces
				continue;
			}
			indices.push_back(f->mIndices[0]);
			indices.push_back(f->mIndices[1]);
			indices.push_back(f->mIndices[2]);
		}

		gameMesh = new Mesh(vertices, indices, cam);
	}

}
