#pragma once

#include "framework.h"

#include <d3d9.h>
#pragma comment (lib,"d3d9.lib")

#include <d3dx9.h>
#pragma comment (lib,"d3dx9.lib")

class Viewer {
public:

	class Texture {
	public:
		Texture () = default;

		Texture ( Texture&& ) = delete;
		Texture ( const Texture& ) = delete;
		Texture& operator=( Texture&& ) = delete;
		Texture& operator=( const Texture& ) = delete;

		constexpr operator bool () const noexcept { return _data != nullptr; }
		constexpr auto& data () const noexcept { return _data; }
		constexpr auto& size () const noexcept { return _size; }

		void load ( const Viewer& viewer, const char* path ) noexcept;
		void load ( const Viewer& viewer, const wchar_t* path ) noexcept;

	private:
		ImVec2 _size;
		LPDIRECT3DTEXTURE9 _data;
	};

	Viewer ( HWND ) noexcept;
	~Viewer () noexcept;

	Viewer ( Viewer&& ) = delete;
	Viewer ( const Viewer& ) = delete;
	Viewer& operator=( Viewer&& ) = delete;
	Viewer& operator=( const Viewer& ) = delete;

	void reset () noexcept;
	void resize ( WPARAM, LPARAM ) noexcept;

	LPDIRECT3D9             Direct3D9;
	LPDIRECT3DDEVICE9       Direct3DDevice9;
	D3DPRESENT_PARAMETERS   Direct3DParams;

	std::unordered_map<std::string, Texture> textures;

	///////////////////
	// ImGui Helper  //
	///////////////////
	class Position {
	public:
		enum class Type {
			CURSOR,
			CENTER
		};
		Position ( Type type = Type::CURSOR ) noexcept;
		constexpr auto& data () noexcept { return position; }
	private:
		ImVec2 position;
	};

	///////////////////
	// ImGui Widgets //
	///////////////////
	class Widget {
	protected:
		Widget () = default;

		Widget ( Widget&& ) = delete;
		Widget ( const Widget& ) = delete;
		Widget& operator=( Widget&& ) = delete;
		Widget& operator=( const Widget& ) = delete;

		bool draw;
	public:
		constexpr operator bool () const noexcept { return draw; }
	};

	class Frame : public Widget {
	public:
		class Button {
			friend Frame;
		public:
			Button ( const char* id, const Texture& texture, const Texture& textureHovered, const ImVec2& position, const ImVec2& size, float rounding = ImGui::GetStyle ().FrameRounding ) noexcept;
			Button ( const char* id, const ImVec4& color, const ImVec4& colorActive, const ImVec4& colorHovered, const ImVec2& position, const ImVec2& size, float rounding = ImGui::GetStyle ().FrameRounding ) noexcept;
			~Button () noexcept;

			struct Data { bool isClicked, isHovered; };
			const Data& data () const noexcept;
		private:
			static std::unordered_map<std::string, Data> buttons;
			Data* button;
		};

		Frame ( const char* id, const Texture& texture ) noexcept;
		~Frame () noexcept;

	private:
		static const char* frames;
	};
};