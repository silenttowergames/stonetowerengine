#pragma once

// Stone Tower Engine
// Silent Tower Games LLC

// Application
#include "Application/ApplicationState.h"
#include "Application/ApplicationStateFunctions.c"
#include "Application/Config.h"
#include "Application/ConfigFunctions.c"

// Assets
#include "Assets/ASEpriteJSON.h"
#include "Assets/ASEpriteJSONFunctions.c"
#include "Assets/AssetManager.h"
#include "Assets/AssetManagerFunctions.c"
#include "Assets/Font.h"
#include "Assets/FontFunctions.c"
#include "Assets/FontStashFNA3DFunctions.c"
#include "Assets/LuaScript.h"
#include "Assets/LuaScriptFunctions.c"
#include "Assets/Shader.h"
#include "Assets/ShaderFunctions.c"
#include "Assets/Texture.h"
#include "Assets/TextureFunctions.c"
#include "Assets/TiledJSON.h"
#include "Assets/TiledJSONFunctions.c"
#include "Assets/TiledJSONLayer.h"
#include "Assets/TiledJSONObject.h"
#include "Assets/TiledJSONProperty.h"

// Audio
#include "Audio/AudioManager.h"
#include "Audio/AudioManagerFunctions.c"
#include "Audio/Play.h"
#include "Audio/Sound.h"
#include "Audio/SoundFunctions.c"
#include "Audio/SoundInstanceFunctions.c"

// Debug
#include "Debug/ConsoleState.h"
#include "Debug/ConsoleCommandFunctions.c"

// ECS
// Components
#include "ECS/Components/AINPC.h"
#include "ECS/Components/AIPlayer.h"
#include "ECS/Components/Animate.h"
#include "ECS/Components/BasicAABB.h"
#include "ECS/Components/Body.h"
#include "ECS/Components/CameraFollow.h"
#include "ECS/Components/Hitbox.h"
#include "ECS/Components/HitboxFunctions.c"
#include "ECS/Components/Menu.h"
#include "ECS/Components/MenuItem.h"
#include "ECS/Components/PauseMenu.h"
#include "ECS/Components/Renderable.h"
#include "ECS/Components/RenderableFunctions.c"
#include "ECS/Components/RenderOffsetFunctions.c"
#include "ECS/Components/TiledMap.h"
#include "ECS/Components/TiledObject.h"
#include "ECS/Components/TileLayerCollides.h"
// Entities
#include "ECS/Entities/Factory.h"
#include "ECS/Entities/NPCFactory.c"
#include "ECS/Entities/PlayerFactory.c"
#include "ECS/Entities/TestMenuFactory.c"
#include "ECS/Entities/TextBoxFactory.c"
// Systems
#include "ECS/Systems/AINPCSystem.c"
#include "ECS/Systems/AnimateSystem.c"
#include "ECS/Systems/BasicAABBSystem.c"
#include "ECS/Systems/CameraFollowSystem.c"
#include "ECS/Systems/ConsoleStateSystem.c"
#include "ECS/Systems/DebugMovableSystem.c"
#include "ECS/Systems/DepthSystem.c"
#include "ECS/Systems/DrawSystem.c"
#include "ECS/Systems/EngineUpdateSystem.c"
#include "ECS/Systems/FinalizeScreenSystem.c"
#include "ECS/Systems/MenuSystem.c"
#include "ECS/Systems/MoveSystem.c"
#include "ECS/Systems/PauseMenuSystem.c"
#include "ECS/Systems/SDLEventsSystem.c"
// .
#include "ECS/FlecsFunctions.c"
#include "ECS/SortByLayerThenY.c"

// GameData
#include "GameData/GameData.h"
#include "GameData/GameDataAttribute.h"
#include "GameData/GameDataFunctions.c"

// Input
#include "Input/GamepadButtons.h"
#include "Input/GamepadButtonsFunctions.c"
#include "Input/GamepadState.h"
#include "Input/GamepadStateFunctions.c"
#include "Input/InputManager.h"
#include "Input/InputManagerFunctions.c"
#include "Input/KeyboardState.h"
#include "Input/KeyboardStateFunctions.c"
#include "Input/MouseState.h"
#include "Input/MouseStateFunctions.c"

// Logger
#include "Logging/Logger.h"
#include "Logging/LoggerFunctions.c"

// Rendering
#include "Rendering/Camera.h"
#include "Rendering/CameraFunctions.c"
#include "Rendering/Matrix.h"
#include "Rendering/MatrixFunctions.c"
#include "Rendering/RenderingFunctions.c"
#include "Rendering/RenderState.h"
#include "Rendering/RenderStateFunctions.c"
#include "Rendering/RenderTarget.h"
#include "Rendering/RenderTargetFunctions.c"
#include "Rendering/SpriteBatch.h"
#include "Rendering/SpriteBatchFunctions.c"

// Scenes
#include "Scenes/Scene.h"

// Utilities
#include "Utilities/color.h"
#include "Utilities/colorFunctions.c"
#include "Utilities/float2d.h"
#include "Utilities/float4d.h"
#include "Utilities/int2d.h"
#include "Utilities/quad.h"
#include "Utilities/quadFunctions.c"
#include "Utilities/split.c"
#include "Utilities/wallsFunctions.c"
