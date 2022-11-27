#include "model.h"

Model::Model(const std::string& path)
	:dir(path), debugger("Model")
{
	std::cout << "[INFO]  [Model::Loading> " << path << std::endl;
	LoadModel();
}

void Model::RenderModel()
{
	for (size_t i = 0; i < m_meshList.size(); i++)
	{
		unsigned int materialIndex = m_textureID[i];

		if (materialIndex < m_textureList.size() && m_textureList[materialIndex])
		{
			m_textureList[materialIndex]->Bind();
			m_meshList[i]->RenderMesh();
		}
		else
		{
			m_meshList[i]->RenderMesh();
		}
	}
}

void Model::LoadModel()
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(dir.getPath(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		debugger.giveMessage(DebugLevel::Error, "LoadModel::Assimp", importer.GetErrorString());
		return;
	}

	processNode(scene->mRootNode, scene);
	processTexture(scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
	for (size_t i = 0; i < node->mNumMeshes; i++)
	{
		m_meshList.push_back(processMesh(scene->mMeshes[node->mMeshes[i]], scene));
	}
	for (size_t i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

Mesh* Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	for (size_t i = 0; i < mesh->mNumVertices; i++)
	{
		glm::vec3 data;

		//Get Vertex data
		Vertex vertex;
		data.x = mesh->mVertices[i].x;
		data.y = mesh->mVertices[i].y;
		data.z = mesh->mVertices[i].z;
		vertex.Position = data;

		//Get Normal data
		data.x = -mesh->mNormals[i].x;
		data.y = -mesh->mNormals[i].y;
		data.z = -mesh->mNormals[i].z;
		vertex.Normal = data;

		//Get Texture Coordinates if any exists
		if (mesh->mTextureCoords[0])
		{
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoord = vec;
		}
		else
		{
			vertex.TexCoord = glm::vec2(0.0f, 0.0f);
		}
		vertices.push_back(vertex);
	}

	//Get Index data
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	m_textureID.push_back(mesh->mMaterialIndex);
	return new Mesh(vertices, indices);
}

void Model::processTexture(const aiScene* scene)
{
	m_textureList.resize(scene->mNumMaterials);
	for (size_t i = 0; i < scene->mNumMaterials; i++)
	{
		m_textureList[i] = nullptr;

		aiMaterial* material = scene->mMaterials[i];
		if (material->GetTextureCount(aiTextureType_DIFFUSE))
		{
			aiString path;
			if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
			{
				int idx = std::string(path.data).rfind("\\");
				std::string filename = std::string(path.data).substr(idx + 1);

				std::string texPath = std::string("/res/texture/") + dir.getFileName() + "/" + filename;
				debugger.giveMessage(DebugLevel::Info, "Model::Loading::Texture", texPath);

				m_textureList[i] = new Texture(texPath);

				if (!m_textureList[i]->LoadTexture())
				{
					debugger.giveMessage(DebugLevel::Error, "Model::texture::Failed to load a texture", texPath);
					delete m_textureList[i];
					m_textureList[i] = nullptr;
				}
			}
		}
		if (!m_textureList[i])
		{
			m_textureList[i] = new Texture("/res/texture/plain.png");
			m_textureList[i]->LoadTexture();
		}
	}
}

Model::~Model()
{
	for (size_t i = 0; i < m_meshList.size(); i++)
	{
		delete m_meshList[i];
	}
	for (size_t i = 0; i < m_textureList.size(); i++)
	{
		delete m_textureList[i];
	}
}