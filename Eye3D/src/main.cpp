#define GLEW_STATIC
#include "common.h"

#include "render/TestImage.h"
#include "render/TestFont.h"

bool quit;

SDL_Window* window;
SDL_GLContext glContext;
SDL_Event sdlEvent;

void storeTextureData(int const width,
	int const height,
	FT_Bitmap & bitmap,
	std::vector<GLubyte> & expanded_data)
{
	// Note: two channel bitmap (One for
	// channel luminosity and one for alpha).
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			expanded_data[2 * (i + j * width)] = 255; // luminosity
			expanded_data[2 * (i + j * width) + 1] =
				(i >= bitmap.width || j >= bitmap.rows) ? 0 :
				bitmap.buffer[i + bitmap.width * j];
		}
	}
}

int main(int argc, char *argv[])
{

	//FT_Library library;
	//if (FT_Init_FreeType(&library))
	//	exit(0);
	//FT_Face    m_FT_Face;
	//if (FT_New_Face(library, "D:/Project/c++/glLFont/font/华康少女文字.ttf", 0, &m_FT_Face))
	//	exit(0);
	//FT_Set_Char_Size(m_FT_Face, 20 * 64.0, 20 * 64.0, 0, 0);
	//FT_Select_Charmap(m_FT_Face, FT_ENCODING_UNICODE);
	//std::wstring ss = L"我爱你";
	//FT_Load_Char(m_FT_Face, ss[0], FT_LOAD_RENDER | FT_LOAD_NO_HINTING);

	//FT_Glyph glyph;
	//FT_Get_Glyph(m_FT_Face->glyph, &glyph);

	//FT_Bitmap& bitmap = m_FT_Face->glyph->bitmap;
	//int width = next_p2(bitmap.width);
	//int height = next_p2(bitmap.rows);

	//std::vector<GLubyte> expanded_data(2 * width * height, 0);
	//storeTextureData(width, height, bitmap, expanded_data);



	quit = false;

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	else
	{
		window = SDL_CreateWindow("Uxin DeepEye", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			return false;
		}
		else
		{
			glContext = SDL_GL_CreateContext(window);
			if (glContext == NULL)
			{
				printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
				return false;
			}
			else
			{
				glewInit();
			}
		}
	}
	UxDeepEye::CTestImage *testImage = new UxDeepEye::CTestImage();
	UxDeepEye::CTestFont *testFont = new UxDeepEye::CTestFont();

	while (!quit)
	{
		while (SDL_PollEvent(&sdlEvent) != 0)
		{
			if (sdlEvent.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		glViewport(0, 0, 800, 600);
		glClearColor(0.0f, 0.0f, 0.0f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		testImage->DrawFrame();
		testFont->DrawFrame();

		SDL_GL_SwapWindow(window);
	}

	SDL_DestroyWindow(window);
	window = NULL;

	SDL_Quit();

	return 0;
}