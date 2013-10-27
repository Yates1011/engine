#pragma once

#include <map>
#include <vector>
#include "../defines.h"
#include "../Helpers/Helpers.h"
#include "Font.h"
#include "../Components/TransformComponent.h"
#include "../Graphics/Color.h"
#include "../Graphics/Shader.h"

#include "ft2build.h"
#include "freetype/freetype.h"

#ifdef DESKTOP
#include <glew.h>
#else
#include <GLES/gl.h>
#include <GLES/glext.h>
#endif

namespace star
{
	class Texture2D;
	class Filepath;

	struct TextDesc
	{
		TextDesc()
			:Text(EMPTY_STRING)
			,Fontname(EMPTY_STRING)
			,TransformComp(nullptr)
			,TextColor(Color::Black)
		{}
		tstring Text;
		tstring Fontname;
		Color TextColor;
		TransformComponent* TransformComp; 
	};

	class FontManager
	{
	public:
		~FontManager(void) {}

		static FontManager * GetInstance();

		bool LoadFont(const tstring& path, const tstring& name, int32 size);
		const Font& GetFont(const tstring& name);
		bool DeleteFont(const tstring& name);
		void EraseFonts();
		bool DrawText(const tstring& text, const tstring& fontname,TransformComponent* transform, Color color = Color::Black);
		bool DrawText(TextDesc textDesc);
	private:
		//Data Members
		static FontManager * mFontManager;

		FT_Library mLibrary;

		std::map<tstring, Font> mFontList;
		std::vector<tstring> mPathList;

		Shader m_Shader;

		FontManager(void);
		mat4x4 InverseMatrix(const mat4x4& matrix);
		void SplitIntoLines(std::vector<std::string> &list, const std::string &string);
		tstring CheckWrapping(Font& font, const tstring& stringIn,const int32& wrapWidth);
		void SplitString(std::vector<tstring>& wordArrayIn,const tstring& stringIn, const tstring& delimiter);

		FontManager(const FontManager& yRef);
		FontManager(FontManager&& yRef);
		FontManager& operator=(const FontManager& yRef);
	};
}