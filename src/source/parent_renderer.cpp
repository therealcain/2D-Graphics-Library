#include "../include/parent_renderer.hpp"

#ifdef _WIN32
#include "../include/windows/renderer.hpp"
#elif __linux__
#include "../include/linux/renderer.hpp"
#endif

START_NAMESPACE

const std::string& ParentRenderer::get_title() const {
    return m_title;
}

// ------------------------------------------------------------ //

const Geometry& ParentRenderer::get_geometry() const {
    return m_geometry;
}

// ------------------------------------------------------------ //

void ParentRenderer::close() {
    running = false;
}

// ------------------------------------------------------------ //

double ParentRenderer::get_framerate() const 
{
    using namespace std::chrono;

    high_resolution_clock::time_point current_ticks = high_resolution_clock::now();

    auto delta_ticks = duration_cast<duration<double>>(current_ticks - start_ticks);

    if (delta_ticks.count() > 0)
        return 1.0 / delta_ticks.count();

    return 0.0;
}

// ------------------------------------------------------------ //

bool ParentRenderer::is_focused() const {
    return focused;
}

END_NAMESPACE