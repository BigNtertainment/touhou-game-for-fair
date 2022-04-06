#pragma once

#include <vector>
#include <algorithm>
#include <functional>
#include "box2d/box2d.h"
#include "glad.h"
#include <GLFW/glfw3.h>
#include "../entity/entity.h"
#include "../vector2/vector2.h"
#include "../../global/game/game.h"
#include "../../global/input/input.h"
#include "types/prefab/prefab.h"

namespace BigNgine {
	class Scene;

	
	using SceneStartFunction = std::function<void(BigNgine::Scene*)>;
	using SceneUpdateFunction = std::function<void(BigNgine::Scene*, int)>;
}

namespace Input {
	class Callback;
}

namespace BigNgine {
	class Entity;
	class Prefab;
	class Behaviour;
	
	class Scene {
		friend Entity;
		friend Behaviour;
	public:
		Entity* Camera;
		float CameraZoom;

		b2Vec2* gravity;
		b2World* world;

		Scene(SceneStartFunction Start, SceneUpdateFunction Update);

		///	Adds entity to Scene
		///	@param entity BigNgine::Entity entity to be added to scene
		void AddEntity(Entity* entity);

		/// Creates entity from prefab and adds it to scene
		/// @param prefab the prefab to be added to the scene
		/// @param args arguments to be passed to prefab
		BigNgine::Entity* AddPrefab(Prefab& prefab, void* args[] = {}, std::function<void(Entity* creation)> callback = [] (Entity*) {});

		///	Adds callback to Scene
		///	@param callback Input::Callback callback to be added to scene
		void AddCallback(Input::Callback* callback);

		/// Removes the entity from the scene and deletes it
		/// @param entity the entity to be removed from the scene
		void RemoveEntity(Entity* entity);

		int GetActiveTime();

		void Start();
		void Update(int deltaTime);

		~Scene();

		static std::vector<Scene*> GetScenes();
		std::vector<Input::Callback*> GetCallbacks();
		std::vector<Entity*> GetEntities();
	private:
		std::vector<Entity*> entities = std::vector<Entity*>();
		std::vector<Input::Callback*> callbacks = std::vector<Input::Callback*>();

		static std::vector<Scene*> scenes;

		SceneStartFunction _Start;
		SceneUpdateFunction _Update;
		
		unsigned int activeTime = 0;
	};
}