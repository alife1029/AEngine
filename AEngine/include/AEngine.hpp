#ifndef AENGINE_HEADER_HPP
#define AENGINE_HEADER_HPP

#include "AE_API.hpp"

// Application headers
#include "AEngine/Application/Application.hpp"
#include "AEngine/Application/Window.hpp"
#include "AEngine/Application/FileDialogs.hpp"
#include "AEngine/Application/AppConfig.hpp"

// Exception Handling headers
#include "AEngine/Exception/Exception.hpp"
#include "AEngine/Exception/InitializationException.hpp"
#include "AEngine/Exception/OpenGLException.hpp"

// Graphic headers
#include "AEngine/Graphics/Renderer2D.hpp"
#include "AEngine/Graphics/OrhographicCamera.hpp"
#include "AEngine/Graphics/TextRenderer.hpp"

// Input & Event Handling Headers
#include "AEngine/Input/EventSystem.hpp"
#include "AEngine/Input/Input.hpp"
#include "AEngine/Input/Keys.hpp"

// Scene and ECS Headers
#include "AEngine/Scene/Scene.hpp"
#include "AEngine/Scene/SceneManager.hpp"
#include "AEngine/Scene/Entity.hpp"

// Components
#include "AEngine/Scene/Components/Transform.hpp"
#include "AEngine/Scene/Components/SpriteRenderer.hpp"

// Utility Headers
#include "AEngine/Utils/Logger.hpp"
#include "AEngine/Utils/Time.hpp"

// Math headers
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#endif
