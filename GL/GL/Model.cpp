#include "Model.h"

// Always Base colour  -->  Normal
Model::Model(const string& filePath, string materialPaths[])
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
		| aiProcess_FlipUVs
		| aiProcess_GenNormals
	);

	if (!scene)
	{
		print("Couldn't import model")
		return;
	}

	for (int i = 0; i < scene->mNumMeshes; i++) 
	{
		const aiMesh* mesh = scene->mMeshes[i];
		vector<GLfloat> vertices;
		vector<GLuint> indices;


		///// Vertex data
		for (int j = 0; j < mesh->mNumVertices; j++) {

			// Pushing the position
			const aiVector3D* pos = &mesh->mVertices[j];
			vertices.push_back(pos->x);
			vertices.push_back(pos->y);
			vertices.push_back(pos->z);

			// Pushing the normals
			if (mesh->HasNormals())
			{
				const aiVector3D* n = &mesh->mNormals[j];

				vertices.push_back(n->x);
				vertices.push_back(n->y);
				vertices.push_back(n->z);
			}


			// Pushing the tex coords
			// Check if there are any present
			if (!mesh->HasTextureCoords(0)) continue;

			const aiFace* f = &mesh->mFaces[j];
			
			vertices.push_back(mesh->mTextureCoords[0][j].x);
			vertices.push_back(mesh->mTextureCoords[0][j].y);
		}


		///// Inidices
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
			
		if (scene->mNumMeshes == 1) gameMesh = new Mesh(vertices, indices, materialPaths);
		else
		{
			Mesh* newMesh = new Mesh(vertices, indices, materialPaths);
			gameMeshes.push_back(newMesh);
		}
	}
	print(scene->mNumMeshes)

	// Once the mesh/meshes have been added, there's no need for the scene.
	importer.FreeScene();
}

void Model::Render(Camera* cam, Light light) const
{
	if (gameMesh) gameMesh->Render(cam, light); 
	else
	{
		for(const auto& mesh : gameMeshes) if(mesh) mesh->Render(cam, light);
	}	

}

glm::vec3 Model::GetPosition() const
{
	if (gameMesh) return gameMesh->GetPosition();
	else return gameMeshes[0]->GetPosition();
}

glm::vec3 Model::GetRotation() const
{
	if (gameMesh) return gameMesh->GetRotation();
	else return gameMeshes[0]->GetRotation();
}

glm::vec3 Model::GetScale() const
{
	if (gameMesh) return gameMesh->GetScale();
	else return gameMeshes[0]->GetScale();
}





void Model::SetTransform(const float px, const float py, const float pz, const float rx, const float ry, const float rz, const float sx, const float sy, const float sz) const
{
	if (gameMesh) gameMesh->SetTransform({ px,py,pz }, { rx,ry,rz }, { sx,sy,sz });
	else
	{
		for (const auto& mesh : gameMeshes) if (mesh) mesh->SetTransform({ px,py,pz }, { rx,ry,rz }, { sx,sy,sz });;
	}
	
}

//////////////////////////////////// TRANSFORMS ////////////////////////////////////
void Model::SetPosition(const glm::vec3 newVal) const
{
	if (gameMesh) gameMesh->SetPosition(newVal);
	else
	{
		for (const auto& mesh : gameMeshes) if (mesh) mesh->SetPosition(newVal);
	}
}

void Model::SetPosition(const float x, const float y, const float z) const
{
	if (gameMesh) gameMesh->SetPosition(x, y, z);
	else
	{
		for (const auto& mesh : gameMeshes) if (mesh) mesh->SetPosition(x, y, z);
	}
}

void Model::AddPosition(const glm::vec3 newVal) const
{
	if (gameMesh) gameMesh->AddPosition(newVal);
	else
	{
		for (const auto& mesh : gameMeshes) if (mesh) mesh->AddPosition(newVal);
	}
}

void Model::AddPosition(const float x, const float y, const float z) const
{
	if (gameMesh) gameMesh->AddPosition(x, y, z);
	else
	{
		for (const auto& mesh : gameMeshes) if (mesh) mesh->AddPosition(x, y, z);
	}
}

void Model::SetRotation(const glm::vec3 newVal) const
{
	if (gameMesh) gameMesh->SetRotation(newVal);
	else
	{
		for (const auto& mesh : gameMeshes) if (mesh) mesh->SetRotation(newVal);
	}
}

void Model::SetRotation(const float x, const float y, const float z) const
{
	if (gameMesh) gameMesh->SetRotation(x, y, z);
	else
	{
		for (const auto& mesh : gameMeshes) if (mesh) mesh->SetRotation(x, y, z);
	}
}

void Model::LookAtRotation(glm::mat4 matrix)
{
	if (gameMesh) gameMesh->LookAtRotation(matrix);
	else
	{
		for (const auto& mesh : gameMeshes) if (mesh) mesh->LookAtRotation(matrix);
	}
}

void Model::AddRotation(const glm::vec3 newVal) const
{
	if (gameMesh) gameMesh->AddRotation(newVal);
	else
	{
		for (const auto& mesh : gameMeshes) if (mesh) mesh->AddRotation(newVal);
	}
}

void Model::AddRotation(const float x, const float y, const float z) const
{
	if (gameMesh) gameMesh->AddRotation(x, y, z);
	else
	{
		for (const auto& mesh : gameMeshes) if (mesh) mesh->AddRotation(x, y, z);
	}
}

void Model::SetScale(const glm::vec3 newVal) const
{
	if (gameMesh) gameMesh->SetScale(newVal);
	else
	{
		for (const auto& mesh : gameMeshes) if (mesh) mesh->SetScale(newVal);
	}
}

void Model::SetScale(const float x, const float y, const float z) const
{
	if (gameMesh) gameMesh->SetScale(x, y, z);
	else
	{
		for (const auto& mesh : gameMeshes) if (mesh) mesh->SetScale(x, y, z);
	}
}

void Model::CreateMaterial(const std::string texturePath[]) const
{
	if(gameMesh) gameMesh->CreateMaterial(texturePath);
	else
	{
		for (const auto& mesh : gameMeshes) if (mesh) mesh->CreateMaterial(texturePath);
	}
}


void Model::SetCollisionsEnabled(const bool value) const
{
	if(gameMesh) gameMesh->SetCollision(value);
	else
	{
		for (const auto& mesh : gameMeshes) if (mesh) mesh->SetCollision(value);
	}
}

void Model::SetVisibility(bool value) const
{
	if (gameMesh) gameMesh->SetVisibility(value);
	else
	{
		for (const auto& mesh : gameMeshes) if (mesh) mesh->SetVisibility(value);
	}
}

void Model::EnableTextureWrapping() const
{
	if (gameMesh) gameMesh->EnableTextureWrapping();
	else
	{
		for (const auto& mesh : gameMeshes) if (mesh) mesh->EnableTextureWrapping();
	}
}
