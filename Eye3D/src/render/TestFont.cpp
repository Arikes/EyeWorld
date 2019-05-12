#include "TestFont.h"
#include "../util/RenderUtil.h"

inline int next_p2(int a)
{
	int rval = 1;
	// rval<<=1 Is A Prettier Way Of Writing rval*=2;
	while (rval<a) rval <<= 1;
	return rval;
}

namespace UxDeepEye {
	CTestFont::CTestFont() :_shaderReady(false) {

	}

	CTestFont::~CTestFont() {
	}

	void CTestFont::DrawFrame() {
		if (!_shaderReady) {
			_programHandle = CRenderUtil::loadProgram(vsh2, fsh2);
			CfgShader();
			_texture = new CTexture("C:/Users/Aerk/Pictures/ResTest/aisi.jpg");

			FT_Library library;
			if (FT_Init_FreeType(&library))
				exit(0);
			FT_Face    m_FT_Face;
			if (FT_New_Face(library, "D:/Project/c++/glLFont/font/华康少女文字.ttf", 0, &m_FT_Face))
				exit(0);
			FT_Set_Char_Size(m_FT_Face, 20 * 64.0, 20 * 64.0, 0, 0);
			FT_Select_Charmap(m_FT_Face, FT_ENCODING_UNICODE);
			std::wstring ss = L"操";
			FT_Load_Char(m_FT_Face, ss[0], FT_LOAD_RENDER | FT_LOAD_NO_HINTING);

			FT_Glyph glyph;
			FT_Get_Glyph(m_FT_Face->glyph, &glyph);

			FT_Bitmap& bitmap = m_FT_Face->glyph->bitmap;
			int width = next_p2(bitmap.width);
			int height = next_p2(bitmap.rows);

			std::vector<GLubyte> expanded_data(2 * width * height, 0);
			//storeTextureData(width, height, bitmap, expanded_data);
			for (int j = 0; j < height; j++) {
				for (int i = 0; i < width; i++) {
					expanded_data[2 * (i + j * width)] = 255; // luminosity
					expanded_data[2 * (i + j * width) + 1] =
						(i >= bitmap.width || j >= bitmap.rows) ? 0 :
						bitmap.buffer[i + bitmap.width * j];
				}
			}

			GLuint texName[1];
			glGenTextures(1, texName);
			glBindTexture(GL_TEXTURE_2D, texName[0]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

			// Create the texture Itself
			// GL_LUMINANCE_ALPHA to indicate 2 channel data.
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
				GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, &expanded_data.front());
			_textureFont = texName[0];
			_shaderReady = true;
		}

		glUseProgram(_programHandle);
		GLfloat verts[] = {
			-0.2,-0.2,0.0,
			0.2,-0.2,0.0,
			-0.2,0.2,0.0,
			0.2,0.2,0.0
		};

		GLfloat texcoords[] = {
			0.0,1.0,
			1.0,1.0,
			0.0,0.0,
			1.0,0.0
		};

		GLubyte indices[] = {
			0,1,2,
			1,3,2
		};
		glEnableVertexAttribArray(_positionHandle);
		glEnableVertexAttribArray(_texcoordHandle);

		glVertexAttribPointer(_positionHandle, 3, GL_FLOAT, GL_FALSE, 0, verts);
		glEnableVertexAttribArray(_positionHandle);

		glVertexAttribPointer(_texcoordHandle, 2, GL_FLOAT, GL_FALSE, 0, texcoords);
		glEnableVertexAttribArray(_texcoordHandle);

		glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, _texture->GetTexture());
		glBindTexture(GL_TEXTURE_2D, _textureFont);
		glUniform1i(_texcoordHandle, 0);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_BYTE, indices);
		glDisable(GL_BLEND);
		std::cout << "CTestImage DrawFrame" << std::endl;
	}

	void CTestFont::CfgShader() {
		glUseProgram(_programHandle);
		_positionHandle = glGetAttribLocation(_programHandle, "position");
		_texcoordHandle = glGetAttribLocation(_programHandle, "texcoord");
		_textureHandle = glGetUniformLocation(_programHandle, "texture");
	}
}