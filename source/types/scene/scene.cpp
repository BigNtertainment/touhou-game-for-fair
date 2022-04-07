#include "./scene.h"

std::vector<BigNgine::Scene *> BigNgine::Scene::scenes = std::vector<BigNgine::Scene*>();

BigNgine::Scene::Scene(const SceneStartFunction &Start, const SceneUpdateFunction &Update)
{
	_Start = Start;
	_Update = Update;
	
	Scene::scenes.push_back(this);
}

void BigNgine::Scene::AddEntity(Entity *entity)
{
	// Set the entity parent scene
	entity->parentScene = this;
	
	// Add the entity to the scene entities vector
	entities.push_back(entity);
	
	// If this scene is currently running, call the entity start method
	if (Game::GetInstance()->GetActiveScene() == this)
		entity->Start();
}

BigNgine::Entity* BigNgine::Scene::AddPrefab(Prefab& prefab, void* args[], std::function<void(Entity* creation)> callback) {
	// Create the entity from the prefab
	Entity* entity = prefab.Create(args);

	// Add the entity to the scene
	AddEntity(entity);

	// If a callback was provided, call it
	callback(entity);

	return entity;
}

void BigNgine::Scene::AddEntityToFront(Entity *entity)
{
	// Set the entity parent scene
	entity->parentScene = this;
	
	// Add the entity to the scene entities vector
	entities.insert(entities.begin() + 4, entity);
	
	// If this scene is currently running, call the entity start method
	if (Game::GetInstance()->GetActiveScene() == this)
		entity->Start();
}

void BigNgine::Scene::AddPrefabToFront(Prefab& prefab, void* args[], std::function<void(Entity* creation)> callback) {
	// Create the entity from the prefab
	Entity* entity = prefab.Create(args);

	// Add the entity to the scene
	AddEntityToFront(entity);

	// If a callback was provided, call it
	callback(entity);
}

void BigNgine::Scene::AddCallback(Input::Callback *callback)
{
	callbacks.push_back(callback);
}

std::vector<Input::Callback *> BigNgine::Scene::GetCallbacks()
{
	return callbacks;
}

void BigNgine::Scene::RemoveEntity(Entity* entity) {
	if(entity == nullptr) {
		Logger::Error("Removed entity is nullptr");
		return;
	}

	// Remove the entity from the scene entities vector
	entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());

	// If this scene is currently running, call the entity start method
	delete entity;

	// Set the entity to nullptr to avoid double deletion
	entity = nullptr;
}

int BigNgine::Scene::GetActiveTime()
{
	return activeTime;
}

void BigNgine::Scene::Start()
{
	gravity = new b2Vec2(0.0f, 9.81f);
	world = new b2World(*gravity);
	activeTime = 0;
	
	entities = {};
	callbacks = {};

	Camera = new BigNgine::Entity();
	CameraZoom = 1.0f;
	AddEntity(Camera);
	
	_Start(this);
	for (auto* entity: entities)
	{
		entity->Start();
	}
}

void BigNgine::Scene::Update(int deltaTime)
{
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	
	world->Step(deltaTime / 1000.0, velocityIterations, positionIterations);
	activeTime += deltaTime;
	
	_Update(this, deltaTime);

	size_t size = entities.size();

	for (uint32_t i = 0; i < size; i++)
	{
		if(entities[i] == nullptr) {
			Logger::Error("Entity is nullptr");
			continue;
		}

		BigNgine::Entity* entity = entities[i];


		entity->Update(deltaTime);


		if(entity == nullptr) {
			i --;
		}

		// Update size in case the Update function changed it
		size = entities.size();
	}
}

void BigNgine::Scene::Destroy() {
	for (int i = 0; i < entities.size(); i++)
	{
		// The entity removes itself from the entities array when destroyed
		delete entities[0];
	}

	for (auto* callback : callbacks)
	{
		delete callback;

		callback = nullptr;
	}
	
	entities = {};
	callbacks = {};

	world = nullptr;
	gravity = nullptr;
}

BigNgine::Scene::~Scene()
{
	Destroy();

	Scene::scenes.erase(std::remove(Scene::scenes.begin(), Scene::scenes.end(), this), Scene::scenes.end());
}

std::vector<BigNgine::Scene *> BigNgine::Scene::GetScenes()
{
	return BigNgine::Scene::scenes;
}

std::vector<BigNgine::Entity*> BigNgine::Scene::GetEntities()
{
	return entities;
}