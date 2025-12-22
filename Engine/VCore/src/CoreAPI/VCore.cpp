#include <fmt/color.h>
#include <CoreAPI/VCore.h>
#include <SDL2/SDL.h>
#include <fmt/core.h>

DEFINE_LOG_CATEGORY(CoreAPI);
namespace VulcanCore {

    VCore::VCore(std::uint32_t Flags) {
        if (Instance) {
            throw std::runtime_error("Only one VCore can be initialized");
        }
        
        Instance = this;
        
        if (SDL_Init(Flags) != 0) {
            return;
        }

        SDL_Rect Rect;
        if (SDL_GetDisplayUsableBounds(0, &Rect) != 0) {
            SDL_Quit();
            return;
        }

        ScreenWidth = Rect.w;
        ScreenHeight = Rect.h;
        
    }

    VCore::~VCore() {
        VLOG_INFO(CoreAPI,"Shutting down VCore");
        SDL_Quit();
    }
    
     VCore& VCore::GetInstance() {
        return *Instance;
    }

    const VMath::Vector2i VCore::GetScreenSize() const {
        return VMath::Vector2i(ScreenWidth, ScreenHeight);
    }


    const std::string VCore::GetVersion() {
        SDL_version version;
        SDL_GetVersion(&version);

        std::string Version = "SDL Version : " + std::to_string((int)version.major) + "." + std::to_string((int)version.minor) + "." + std::to_string((int)version.patch);
        return Version;
    }

    bool VCore::PollEvent(SDL_Event& Event) {
        return SDL_PollEvent(&Event) > 0;
    }

    VulcanEngine::VWindow& VCore::CreateWindow(const VulcanEngine::WindowConfig& config) {
        if (Windows.find(config.Title) != Windows.end()) {
            throw std::runtime_error("Window with name " + config.Title + " already exists");
        }

        auto window = VulcanEngine::VWindow::Create(config);
        Windows[config.Title] = window;
        return *window;
    }

    VulcanEngine::Graphics::VRenderer& VCore::CreateRenderer(const VulcanEngine::Graphics::RendererConfig& config) {
        auto renderer = VulcanEngine::Graphics::VRenderer::Create(config);
        Renderers[config.Window.GetTitle()] = renderer;
        return *renderer;
    }

    VulcanEngine::VWindow& VCore::GetWindow(const std::string_view& InWindowName) {
        return *Windows.at(InWindowName.data());
    }

    VulcanEngine::Graphics::VRenderer& VCore::GetRenderer(const std::string_view& InWindowName) {
        return *Renderers.at(InWindowName.data());
    }
}
