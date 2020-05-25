#include "../../include/draws/transformation.hpp"

START_NAMESPACE

Transformation::Transformation()
    : m_translate(1, 1),
      m_scale(1.f, 1.f),
      m_degree(0) {}

// ------------------------------------------------------------ //

void Transformation::set_translate(const VectorI& translate) {
    m_translate = translate;
}

void Transformation::set_translate(int x, int y) {
    m_translate = {x, y};
}

const VectorI& Transformation::get_translate() const {
    return m_translate;
}

// ------------------------------------------------------------ //

void Transformation::set_scale(const VectorF& scale) {
    m_scale = scale;
}

void Transformation::set_scale(float x, float y) {
    m_scale = {x, y};
}

const VectorF& Transformation::get_scale() const {
    return m_scale;
}

// ------------------------------------------------------------ //

void Transformation::set_rotation(float degree) {
    m_degree = degree;
}

float Transformation::get_rotation() const {
    return m_degree;
}

END_NAMESPACE