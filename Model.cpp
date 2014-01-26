#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <gl/freeglut/freeglut.h>
#include "Model.h"
#include "Common.h"

Model::Model(std::string tag) : base(tag) {
}
Model::~Model() {
}
Model* Model::init() {
	base::init();
	return this;
}
void Model::update() {
	base::update();
}
void Model::draw() {
	base::draw();
	glPushMatrix();

	int max_face = face_index.size();
	int current = 0;
	glEnable(GL_TEXTURE_2D);
	for(int i = 0; i < max_face; i++) {
		images[material_index[i]]->apply();
		if(face_index[i] == 3) {
			glBegin(GL_TRIANGLES);
		} else {
			glBegin(GL_QUADS);
		}
		for(int j = 0; j < face_index[i]; j++) {
			glNormal3f(normals[normal_index[current+j]].x, normals[normal_index[current+j]].y, normals[normal_index[current+j]].z);
			glTexCoord2f(texcoords[vertex_index[current+j]].x, texcoords[vertex_index[current+j]].y);
			glVertex3f(vertexies[vertex_index[current+j]].x, vertexies[vertex_index[current+j]].y, vertexies[vertex_index[current+j]].z);
		}
		current += face_index[i];
		glEnd();
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();
}
void Model::release() {
	for each(Image* img in images) {
		img->release();
	}
	base::release();
}
/** 
 * xファイル読み込み
 */
bool Model::load(const char* file_name) {
	FILE* fp = null;
	if(fp = fopen(file_name, "rt")) {
		char key[255];
		char buf[255];
		int depth = 0;

		while(!feof(fp)) {
			// キーワード 読み込み
			ZeroMemory(key,sizeof(key));
			fscanf_s(fp,"%s ",key,sizeof(key));
			// ヘッダー読み飛ばし
			if(strcmp(key,"Header")==0){
				while(strcmp(key,"}")){
					fscanf_s(fp,"%s ",key,sizeof(key));
				}
				continue;
			}
			// テンプレート読み飛ばし
			if(strcmp(key,"template")==0){
				while(strcmp(key,"}")){
					fscanf_s(fp,"%s ",key,sizeof(key));
				}
				continue;
			}
			// 頂点 読み込み
			if(strcmp(key,"Mesh")==0) {
				fgets(buf,sizeof(buf),fp);
				fgets(buf,sizeof(buf),fp);
				int vertex_num = atoi(buf);
				for(int i = 0; i < vertex_num; i++) {
					VECTOR3 vertex;
					fscanf_s(fp,"%f;%f;%f;,",&vertex.x,&vertex.y,&vertex.z);
					vertexies.push_back(vertex);
				}
				//頂点インデックス読み込み
				fgets(buf,sizeof(buf),fp);
				fgets(buf,sizeof(buf),fp);
				while(strchr(buf,';')==NULL){fgets(buf,sizeof(buf),fp);}//空行対策
				int index_num = atoi(buf);
				int v1=0,v2=0,v3=0,v4=0;
				for(int i = 0; i < index_num; i++) {
					int dammy=0;
					fgets(buf,sizeof(buf),fp);
					std::string str = buf;
					std::string::size_type first = str.find_first_not_of(' ');
					std::string::size_type tab = str.find_first_not_of('\t');
					std::string::size_type index = str.find("3;");
					if(index-first-tab==0) {
						sscanf_s(buf,"%d;%d,%d,%d;,",&dammy,&v1,&v2,&v3);
						vertex_index.push_back(v1);
						vertex_index.push_back(v2);
						vertex_index.push_back(v3);
					}
					if(!(index-first-tab==0)) {
						sscanf_s(buf,"%d;%d,%d,%d,%d;,",&dammy,&v1,&v2,&v3,&v4);
						vertex_index.push_back(v1);
						vertex_index.push_back(v2);
						vertex_index.push_back(v3);
						vertex_index.push_back(v4);
					}
					face_index.push_back(dammy);
				}
				continue;
			}
			if(strcmp(key,"MeshMaterialList")==0) {
				fgets(key,sizeof(key),fp);
				fgets(key,sizeof(key),fp);
				fgets(key,sizeof(key),fp);
				int material_index_num = atoi(key);
				int idx;
				for(int i=0;i<material_index_num ;i++) {
					fscanf_s(fp,"%d,",&idx);
					material_index.push_back(idx);
				}
				continue;
			}
			//マテリアル読み込み
			if(strcmp(key,"Material")==0) {
				fgets(key,sizeof(key),fp);
				VECTOR4 color;
				//ディフューズ
				fscanf_s(fp,"%f;%f;%f;%f;;",&color.x,&color.y,&color.z,&color.w);
//				outmtl.MaterialColor.diffuse=(const Color4 &)color;
				//SHININESS
				fscanf_s(fp,"%f;",&color.x);
				//スペキュラー
				fscanf_s(fp,"%f;%f;%f;;",&color.x,&color.y,&color.z);
//				outmtl.MaterialColor.specular= color;
				//エミッシブ
				fscanf_s(fp,"%f;%f;%f;;",&color.x,&color.y,&color.z);
//				outmtl.MaterialColor.ambient= color;
				fscanf_s(fp,"%s",key,sizeof(key));
				// 長さがある＝テクスチャ適用
				Image* img = (new Image())->init();
				if(strcmp(key, "}")) {
					fgets(buf,sizeof(buf),fp);
					fscanf_s(fp,"%s",key,sizeof(key));
					char file_name[256] = {0};
					int num = strlen(key)-3;
					strncpy(file_name, &key[1], num);
					img->load(file_name);
				}
				images.push_back(img);
				continue;
			}
			//法線 読み込み
			if(strcmp(key,"MeshNormals") == 0) {
				fgets(buf,sizeof(buf),fp);
				fgets(buf,sizeof(buf),fp);
				int nor_num = atoi(buf);
				VECTOR3 nor;
				for(int i=0;i<nor_num ;i++) {
					fscanf_s(fp,"%f;%f;%f;,",&nor.x,&nor.y,&nor.z);
					normals.push_back(nor);
				}
				//法線インデックス読み込み
				fgets(buf,sizeof(buf),fp);
				fgets(buf,sizeof(buf),fp);
				int v1=0,v2=0,v3=0,v4=0;
				while(strchr(buf,';') == NULL) {fgets(buf,sizeof(buf),fp);}//空行対策
				int nor_idx_num = atoi(buf);
				for(int i = 0; i < nor_idx_num; i++) {
					int dammy=0;
					fgets(buf,sizeof(buf),fp);
					std::string str = buf;
					std::string::size_type first = str.find_first_not_of(' ');
					std::string::size_type tab = str.find_first_not_of('\t');
					std::string::size_type index = str.find("3;");
					if(index-first-tab==0) {
						sscanf_s(buf,"%d;%d,%d,%d;,",&dammy,&v1,&v2,&v3);
						normal_index.push_back(v1);
						normal_index.push_back(v2);
						normal_index.push_back(v3);
					}
					if(!(index-first-tab==0)) {
						sscanf_s(buf,"%d;%d,%d,%d,%d;,",&dammy,&v1,&v2,&v3,&v4);
						normal_index.push_back(v1);
						normal_index.push_back(v2);
						normal_index.push_back(v3);
						normal_index.push_back(v4);
					}
				}
				continue;
			}
			// テックスコード読み込み
			if(strcmp(key,"MeshTextureCoords") == 0) {
				fgets(buf,sizeof(buf),fp);
				fgets(buf,sizeof(buf),fp);
				int texcoord_num = atoi(buf);
				for(int i = 0; i < texcoord_num; i++) {
					VECTOR2 texcoord;
					fscanf_s(fp,"%f;%f;,",&texcoord.x,&texcoord.y);
					texcoords.push_back(texcoord);
				}
				continue;
			}
		}
		fclose(fp);
		return true;
	}
	char err[128] = {0};
	sprintf(err, "%s : not found file", file_name);
	debug(err);
	return false;
}
