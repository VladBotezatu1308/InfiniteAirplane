#pragma once
#include "LabCamera.h"

#include <Component/SimpleScene.h>
#include <Component/Transform/Transform.h>
#include <Core/GPU/Mesh.h>
#include <queue>


typedef struct {
	float rotation;
	Mesh* mesh;
	float z_pos, x_pos;
} CloudInfo;

typedef struct {
	glm::vec3 position;
	glm::vec3 direction;
	float alpha;
} SmokeInfo;

typedef struct {
	float rotation;
	float local_rotation;
	float z_pos, x_pos;
} FuelInfo;

typedef struct {
	float rotation;
	float local_rotation;
	float z_pos, x_pos;
	bool animate_break;
	float break_scale;
	float alpha;
} EnemyInfo;

class Avion : public SimpleScene
{
public:
	Avion();
	~Avion();

	void Init() override;

private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	//functii ce ofera majoritatea functionalitatilor precum:
	void RotationManager(float deltaTimeSeconds);	//rotatia avionului si a marii
	void CloudManager(float deltaTimeSeconds);		//afisarea si deplasarea norilor
	void SmokeManager(float deltaTimeSeconds);
	void EnemyManager(float deltaTimeSeconds);		//afisarea, deplasarea si coliziunea inamicilor
	void FuelObjManager(float deltaTimeSeconds);	//afisarea, deplasarea si coliziunea obiectelor de tip combustibil
	void SpawnManager();							//generarea de inamici si combustibil
	void UIManager(float deltaTimeSeconds);			//afisarea User Interface
	void AnimationManager(float deltaTimeSeconds);	//calcularea animatiilor (deplasari pe diverse axe ale avionului)

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;

	//functii pentru crearea marii si rendering de diverse tipuri (spre final am realizat ca una singura era suficienta, dar nu am de ce sa mai schimb)
	Mesh* CreateSea(std::string name);
	void RenderBasic(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Texture2D* texture1= NULL, float ambient_light = 0.5f, float alpha = 1.0f);
	void RenderSea(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix);
	void RenderUI(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Texture2D* texture1 = NULL);


	bool debug_mode = true;

	//variabile pentru camera
	bool cameraThirdPerson = false;
	glm::ivec2 resolution;
	Laborator::MyCamera* camera = new Laborator::MyCamera();
	glm::mat4 projectionMatrix;

	//salvarea texturilor se face intr-un map
	std::unordered_map<std::string, Texture2D*> mapTextures;

	//variabile ce indica starile jocului precum si a animatiilor
	bool game_started = true, game_over = false;
	bool starting_animation_ended = false;
	bool end_animation_started = false;
	bool hit_animation = false;
	float hit_animation_timer = -1.0f;

	//cozi in care se salveaza informatii despre nori, inamici si combustibil
	std::vector<Mesh*> cloud_meshes;
	std::queue<CloudInfo> cloud_queue;
	std::queue<CloudInfo> auxiliary_cloud_queue;
	std::queue<SmokeInfo> smoke_queue;
	std::queue<SmokeInfo> auxiliary_smoke_queue;
	std::queue<EnemyInfo> enemy_queue;
	std::queue<EnemyInfo> auxiliary_enemy_queue;
	std::queue<FuelInfo> fuel_queue;
	std::queue<FuelInfo> auxiliary_fuel_queue;

	//variabile ce influenteaza generarea de noi inamici/combustibil
	bool allowed_to_spawn = true;
	int spawn_frequency = 50;
	float min_distance_between_entities = M_PI/20;

	//varaibile ce definesc avionul
	glm::vec2 plane_pos = glm::vec2(-5.0f, -5.0f);
	glm::vec2 initial_plane_pos = glm::vec2(-3.0f, 1.0f);

	float propeller_rotation = 0.0f;
	float rotation_speed = 10 * M_PI;

	float plane_rotation = 0.0f;
	float plane_rotation_speed = M_PI / 2;
	float plane_maximum_rotation = M_PI / 4;
	bool plane_rotates_UP = false, plane_rotates_DOWN = false, plane_should_stabilize = true;
	float stabilization_waiting_time = 0.2f;

	//variabile ce definesc rotatia marii si viteza de rotatie a acesteia (actually, viteza ce afecteaza intregul joc)
	float sea_rotation = 0.0f;
	float sea_rotation_speed = M_PI/16;
	bool accelerating = false;
	bool smokeEnabled = true;

	//variabile de UI
	float fuel_level = 1.0f;
	int lives = 3;
	bool heart_blink_animation = false;
	float blinking_count = 0;

	//dificultate
	float dificulty_adjustment = 0.0f;
};
