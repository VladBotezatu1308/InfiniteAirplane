 #include "Avion.h"

#include <vector>
#include <string>
#include <iostream>
#include <time.h>

#include <Core/Engine.h>

using namespace std;

Avion::Avion()
{
}

Avion::~Avion()
{
}

void Avion::Init()
{
	camera->Set(glm::vec3(0, 1, 5), glm::vec3(0, 0, 1), glm::vec3(0, 1, 1));
	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
	srand(time(NULL));

	// initializarea texturilor puse peste diverse primitive
	{	
		Texture2D* texture_plane = new Texture2D();
		texture_plane->Load2D("Resources/Textures/plane.jpg", GL_CLAMP_TO_BORDER);
		mapTextures["plane"] = texture_plane;

		Texture2D* texture_head = new Texture2D();
		texture_head->Load2D("Resources/Textures/masterracehead.png", GL_CLAMP_TO_BORDER);
		mapTextures["pilot_head"] = texture_head;

		Texture2D* texture_body = new Texture2D();
		texture_body->Load2D("Resources/Textures/masterracebody.png", GL_CLAMP_TO_BORDER);
		mapTextures["pilot_body"] = texture_body;

		Texture2D* texture_white = new Texture2D();
		texture_white->Load2D("Resources/Textures/white.png", GL_CLAMP_TO_BORDER);
		mapTextures["white"] = texture_white;

		Texture2D* texture_red = new Texture2D();
		texture_red->Load2D("Resources/Textures/red.png", GL_CLAMP_TO_BORDER);
		mapTextures["red"] = texture_red;

		Texture2D* texture_cloud = new Texture2D();
		texture_cloud->Load2D("Resources/Textures/cloud_white.png", GL_CLAMP_TO_BORDER);
		mapTextures["cloud"] = texture_cloud;

		Texture2D* texture_fuel_margin = new Texture2D();
		texture_fuel_margin->Load2D("Resources/Textures/fuel_margin.png", GL_CLAMP_TO_BORDER);
		mapTextures["fuel_margin"] = texture_fuel_margin;

		Texture2D* texture_fuel = new Texture2D();
		texture_fuel->Load2D("Resources/Textures/fuel_margin.png", GL_CLAMP_TO_BORDER);
		mapTextures["fuel_margin"] = texture_fuel;

		Texture2D* texture_fuel_fill = new Texture2D();
		texture_fuel_fill->Load2D("Resources/Textures/fuel_fill.png", GL_CLAMP_TO_BORDER);
		mapTextures["fuel_fill"] = texture_fuel_fill;

		Texture2D* texture_heart = new Texture2D();
		texture_heart->Load2D("Resources/Textures/heart.png", GL_CLAMP_TO_BORDER);
		mapTextures["heart"] = texture_heart;

		Texture2D* texture_over = new Texture2D();
		texture_over->Load2D("Resources/Textures/game_over.jpg", GL_CLAMP_TO_BORDER);
		mapTextures["game_over"] = texture_over;

		Texture2D* texture_over_text = new Texture2D();
		texture_over_text->Load2D("Resources/Textures/game_over_text.png", GL_CLAMP_TO_BORDER);
		mapTextures["game_over_text"] = texture_over_text;
	}

	//initializarea meshurilor
	{
		Mesh* mesh = new Mesh("avion");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "avion.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("propeller");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "propeller.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("pilot_head");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "pilot_head.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("pilot_body");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "pilot_body.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("pilot_coat");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "pilot_coat.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("pilot_hair");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "pilot_hair.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = CreateSea("sea");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh1 = new Mesh("cloud1");
		mesh1->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "cloud1.obj");
		meshes[mesh1->GetMeshID()] = mesh1;
		cloud_meshes.push_back(mesh1);

		Mesh* mesh2 = new Mesh("cloud2");
		mesh2->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "cloud2.obj");
		meshes[mesh2->GetMeshID()] = mesh2;
		cloud_meshes.push_back(mesh2);

		Mesh* mesh3 = new Mesh("cloud3");
		mesh3->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "cloud3.obj");
		meshes[mesh3->GetMeshID()] = mesh3;
		cloud_meshes.push_back(mesh3);
	}
	{
		Mesh* mesh = new Mesh("enemy");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "enemy.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("enemy_break");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "enemy_break.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("fuel");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "fuel.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(-1, -1,  1), glm::vec3(0, 1, 1), glm::vec3(0.2, 0.8, 0.2)),
			VertexFormat(glm::vec3(1, -1,  1), glm::vec3(1, 0, 1), glm::vec3(0.9, 0.4, 0.2)),
			VertexFormat(glm::vec3(-1,  1,  1), glm::vec3(1, 0, 0), glm::vec3(0.7, 0.7, 0.1)),
			VertexFormat(glm::vec3(1,  1,  1), glm::vec3(0, 1, 0), glm::vec3(0.7, 0.3, 0.7)),
			VertexFormat(glm::vec3(-1, -1, -1), glm::vec3(1, 1, 1), glm::vec3(0.3, 0.5, 0.4)),
			VertexFormat(glm::vec3(1, -1, -1), glm::vec3(0, 1, 1), glm::vec3(0.5, 0.2, 0.9)),
			VertexFormat(glm::vec3(-1,  1, -1), glm::vec3(1, 1, 0), glm::vec3(0.7, 0.0, 0.7)),
			VertexFormat(glm::vec3(1,  1, -1), glm::vec3(0, 0, 1), glm::vec3(0.1, 0.5, 0.8)),
		};

		vector<unsigned short> indices =
		{
			0, 1, 2,		1, 3, 2,
			2, 3, 7,		2, 7, 6,
			1, 7, 3,		1, 5, 7,
			6, 7, 4,		7, 5, 4,
			0, 4, 1,		1, 4, 5,
			2, 6, 4,		0, 2, 4,
		};

		Mesh* mesh = new Mesh("cube");
		mesh->InitFromData(vertices, indices);
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		vector<glm::vec3> vertices
		{
			glm::vec3(1.0f,   1.0f, 0.0f),
			glm::vec3(1.0f,  -1.0f, 0.0f),
			glm::vec3(-1.0f, -1.0f, 0.0f),
			glm::vec3(-1.0f,  1.0f, 0.0f),
		};

		vector<glm::vec3> normals
		{
			glm::vec3(0, 1, 1),
			glm::vec3(1, 0, 1),
			glm::vec3(1, 0, 0),
			glm::vec3(0, 1, 0)
		};

		vector<glm::vec2> textureCoords
		{
			glm::vec2(1.0f, 0.0f),
			glm::vec2(1.0f, 1.0f),
			glm::vec2(0.0f, 1.0f),
			glm::vec2(0.0f, 0.0f)
		};

		vector<unsigned short> indices =
		{
			0, 1, 3,
			1, 2, 3
		};

		Mesh* mesh = new Mesh("quad");
		mesh->InitFromData(vertices, normals, textureCoords, indices);
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		vector<glm::vec3> vertices
		{
			glm::vec3(-1, -1,  1),
			glm::vec3(1,  1,  1),
			glm::vec3(1, -1, -1),
			glm::vec3(-1,  1, -1)
		};

		vector<unsigned short> indices =
		{
			0,1,3,
			0,2,1,
			0,3,2,
			2,3,1
			
		};

		vector<glm::vec3> normals
		{
			glm::vec3(-1, -1, 1),
			glm::vec3(1, 1, 1),
			glm::vec3(1, -1, -1),
			glm::vec3(-1, 1, -1)
		};

		vector<glm::vec2> textureCoords
		{
			glm::vec2(0.75f, 0.25f),
			glm::vec2(0.75f, 0.75f),
			glm::vec2(0.25f, 0.75f),
			glm::vec2(0.25f, 0.25f)
		};

		Mesh* mesh = new Mesh("fuel");
		mesh->InitFromData(vertices, normals, textureCoords, indices);
		meshes[mesh->GetMeshID()] = mesh;
	}

	//initializarea shaderelor folosite
	{
		Shader* shader = new Shader("ShaderPlane");
		shader->AddShader("Source/Avion/Shaders/VertexShaderPlane.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Avion/Shaders/FragmentShaderPlane.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}
	{
		Shader* shader = new Shader("ShaderSea");
		shader->AddShader("Source/Avion/Shaders/VertexShaderSea.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Avion/Shaders/FragmentShaderSea.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}
	{
		Shader* shader = new Shader("ShaderUI");
		shader->AddShader("Source/Avion/Shaders/VertexShaderUI.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Avion/Shaders/FragmentShaderUI.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}
	{
		Shader* shader = new Shader("ShaderHair");
		shader->AddShader("Source/Avion/Shaders/VertexShaderHair.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Avion/Shaders/FragmentShaderHair.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}
}

void Avion::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(1.0f, 0.77f, 0.67f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Avion::Update(float deltaTimeSeconds)
{
	if (!game_over && dificulty_adjustment <= 50) {
		dificulty_adjustment += 0.2 * deltaTimeSeconds * sea_rotation_speed / (M_PI / 16);
		min_distance_between_entities = M_PI / (20 + 3.6 * dificulty_adjustment);
	}
	

	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(plane_pos, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, plane_rotation, glm::vec3(0, 0, 1));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f, 0.1f, 0.1f));
	RenderBasic(meshes["avion"], shaders["ShaderPlane"], modelMatrix, mapTextures["plane"]);
	RenderBasic(meshes["pilot_head"], shaders["ShaderPlane"], modelMatrix, mapTextures["pilot_head"]);
	RenderBasic(meshes["pilot_body"], shaders["ShaderPlane"], modelMatrix, mapTextures["pilot_body"]);
	RenderBasic(meshes["pilot_coat"], shaders["ShaderPlane"], modelMatrix, mapTextures["white"]);
	RenderBasic(meshes["pilot_hair"], shaders["ShaderHair"], modelMatrix, mapTextures["white"]);

	modelMatrix = glm::rotate(modelMatrix, propeller_rotation, glm::vec3(1.0f, 0.0f, 0.0f));
	RenderBasic(meshes["propeller"], shaders["ShaderPlane"], modelMatrix, mapTextures["white"]);
	propeller_rotation = propeller_rotation >= 2*M_PI ? 0 : (propeller_rotation + rotation_speed * deltaTimeSeconds);
	
	glEnable(GL_CULL_FACE);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, GL_ZERO);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0, -21, 8));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(19, 19, 2));
	modelMatrix = glm::rotate(modelMatrix, sea_rotation, glm::vec3(0, 0, 1));

	if (deltaTimeSeconds < 1) {
		AnimationManager(deltaTimeSeconds);
		RotationManager(deltaTimeSeconds);
		if (game_started) {
			allowed_to_spawn = true;
			EnemyManager(deltaTimeSeconds);
			FuelObjManager(deltaTimeSeconds);
			SpawnManager();
		}
		
		RenderSea(meshes["sea"], shaders["ShaderSea"], modelMatrix);
		SmokeManager(deltaTimeSeconds);
		CloudManager(deltaTimeSeconds);
	}


	glDisable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);
	glDisable(GL_CULL_FACE);

	UIManager(deltaTimeSeconds);
	
}

void Avion::FrameEnd()
{
	//DrawCoordinatSystem(camera->GetViewMatrix(), projectionMatrix);
}

void Avion::RotationManager(float deltaTimeSeconds) {
	if (plane_rotates_UP) {
		if (plane_rotation <= plane_maximum_rotation) {
			if(cameraThirdPerson && starting_animation_ended && !end_animation_started && !game_over)
				camera->RotateThirdPerson_OX(-plane_rotation);
			
			plane_rotation += plane_rotation_speed * deltaTimeSeconds;
			
			if (cameraThirdPerson && starting_animation_ended && !end_animation_started && !game_over)
				camera->RotateThirdPerson_OX(plane_rotation);
		}
		else {
			if (stabilization_waiting_time <= 0.0f) {
				plane_should_stabilize = true;
				plane_rotates_UP = false;
				plane_rotates_DOWN = false;
			}
			else {
				stabilization_waiting_time -= deltaTimeSeconds;
			}
		}
	}
	else if (plane_rotates_DOWN) {
		if (plane_rotation >= -plane_maximum_rotation) {
			if (cameraThirdPerson && starting_animation_ended && !end_animation_started && !game_over)
				camera->RotateThirdPerson_OX(-plane_rotation);

			plane_rotation -= plane_rotation_speed * deltaTimeSeconds;

			if (cameraThirdPerson && starting_animation_ended && !end_animation_started && !game_over)
				camera->RotateThirdPerson_OX(plane_rotation);
		}
		else {
			if (stabilization_waiting_time <= 0.0f) {
				plane_should_stabilize = true;
				plane_rotates_DOWN = false;
				plane_rotates_UP = false;
			}
			else {
				stabilization_waiting_time -= deltaTimeSeconds;
			}
		}
	}
	else if (plane_should_stabilize) {
		stabilization_waiting_time = 0.2f;

		if (cameraThirdPerson && starting_animation_ended && !end_animation_started && !game_over)
			camera->RotateThirdPerson_OX(-plane_rotation);

		if (abs(plane_rotation) < plane_rotation_speed * deltaTimeSeconds) {
			plane_rotation = 0.0f;
		}
		else {
			if (plane_rotation > 0)
				plane_rotation -= plane_rotation_speed * deltaTimeSeconds;
			else
				plane_rotation += plane_rotation_speed * deltaTimeSeconds;
		}

		if (cameraThirdPerson && starting_animation_ended && !end_animation_started && !game_over)
			camera->RotateThirdPerson_OX(plane_rotation);
	}

	sea_rotation += sea_rotation_speed * deltaTimeSeconds;
}

void Avion::CloudManager(float deltaTimeSeconds) {
	int should_spawn = rand() % 40;
	
	if (should_spawn == 0) {
		CloudInfo new_cloud;
		new_cloud.mesh = cloud_meshes[rand() % 3];
		new_cloud.rotation = M_PI/4;
		new_cloud.x_pos = (rand() % 25) / 10.0f + 20.0f;
		new_cloud.z_pos = -(rand() % 45) / 10.0f + 2.0f;
		cloud_queue.push(new_cloud);
	}

	while (!cloud_queue.empty()) {
		CloudInfo cloud = cloud_queue.front();
		cloud_queue.pop();
		
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0, -21, 0));
		modelMatrix = glm::rotate(modelMatrix, cloud.rotation, glm::vec3(0, 0, 1));
		modelMatrix = glm::translate(modelMatrix, glm::vec3(cloud.x_pos, 0, cloud.z_pos));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f, 0.1f, 0.1f));
		modelMatrix = glm::rotate(modelMatrix, (float) M_PI/2, glm::vec3(0, 0, 1));
		RenderBasic(cloud.mesh, shaders["ShaderPlane"], modelMatrix, mapTextures["cloud"], 0.75f);
		cloud.rotation += sea_rotation_speed * deltaTimeSeconds;

		if (cloud.rotation <= M_PI/4 * 3)
			auxiliary_cloud_queue.push(cloud);
	}

	while (!auxiliary_cloud_queue.empty()) {
		CloudInfo cloud = auxiliary_cloud_queue.front();
		auxiliary_cloud_queue.pop();
		cloud_queue.push(cloud);
	}
}

void Avion::SmokeManager(float deltaTimeSeconds) {
	if (accelerating && smokeEnabled) {
		SmokeInfo new_smoke;
		new_smoke.position = glm::vec3(plane_pos.x, plane_pos.y, 0);
		new_smoke.alpha = 1.0f;
		new_smoke.direction = glm::vec3(-1, ((rand() % 101) / 100.0f) - 0.5f, ((rand() % 101) / 100.0f) - 0.5f);
		if(smoke_queue.size() < 20)
			smoke_queue.push(new_smoke);
	}

	glm::mat4 modelMatrix;
	while (!smoke_queue.empty()) {
		SmokeInfo smoke = smoke_queue.front();
		smoke_queue.pop();

		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, smoke.position);
		modelMatrix = glm::rotate(modelMatrix, plane_rotation, glm::vec3(0, 0, 1));
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.5f, 0, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.05f, 0.05f, 0.05f));
		RenderBasic(meshes["cloud1"], shaders["ShaderPlane"], modelMatrix, mapTextures["white"], 0.0f, smoke.alpha);
		smoke.position += smoke.direction * 4.0f * deltaTimeSeconds;
		smoke.alpha -= 4*deltaTimeSeconds;

		if (smoke.alpha >= 0.1f)
			auxiliary_smoke_queue.push(smoke);
		
	}

	while (!auxiliary_smoke_queue.empty()) {
		SmokeInfo smoke = auxiliary_smoke_queue.front();
		auxiliary_smoke_queue.pop();
		smoke_queue.push(smoke);
	}


}

void Avion::EnemyManager(float deltaTimeSeconds) {
	glm::vec3 plane_center = glm::vec3(plane_pos, 0);
	glm::mat4 modelMatrix;

	while (!enemy_queue.empty()) {
		EnemyInfo enemy = enemy_queue.front();
		enemy_queue.pop();

		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0, -21, 0));
		modelMatrix = glm::rotate(modelMatrix, enemy.rotation, glm::vec3(0, 0, 1));
		modelMatrix = glm::translate(modelMatrix, glm::vec3(enemy.x_pos, 0, enemy.z_pos));
		
		if (enemy.animate_break) {
			modelMatrix = glm::rotate(modelMatrix, (float) -M_PI/2, glm::vec3(1, 0, 0));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(enemy.break_scale));
			RenderBasic(meshes["enemy_break"], shaders["ShaderPlane"], modelMatrix, mapTextures["red"], 0.75f, enemy.alpha);
			enemy.break_scale += 3*deltaTimeSeconds;
			enemy.alpha = enemy.alpha - 3*deltaTimeSeconds > 0 ? enemy.alpha - 3*deltaTimeSeconds : 0;
		}
		else {
			modelMatrix = glm::rotate(modelMatrix, enemy.local_rotation, glm::vec3(0, 1, 0));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f, 0.2f, 0.2f));
			RenderBasic(meshes["enemy"], shaders["ShaderPlane"], modelMatrix, mapTextures["red"], 0.75f);
			
			enemy.rotation += sea_rotation_speed * deltaTimeSeconds;
		}


		if (enemy.local_rotation < 2 * M_PI) {
			enemy.local_rotation += 20 * sea_rotation_speed * deltaTimeSeconds;
		}
		else {
			enemy.local_rotation += -2 * M_PI;
			enemy.local_rotation += 20 * sea_rotation_speed * deltaTimeSeconds;
		}

		if (enemy.rotation <= M_PI / 4 + min_distance_between_entities)
			allowed_to_spawn = false;
		
		if (enemy.rotation >= M_PI / 2 && !enemy.animate_break) {
			glm::vec3 enemy_center = glm::vec3(modelMatrix[3][0], modelMatrix[3][1], modelMatrix[3][2]);
			glm::vec3 collision_test = enemy_center;
			glm::vec3 offset = glm::vec3(0.3f, 0.1f, 0.3f);
			offset = glm::mat3(glm::rotate(glm::mat4(1), plane_rotation, glm::vec3(0, 0, 1))) * offset;

			if (enemy_center.x > plane_center.x + offset.x) {
				collision_test.x = plane_center.x + offset.x;
			}
			if (enemy_center.x < plane_center.x - offset.x) {
				collision_test.x = plane_center.x - offset.x;
			}
			if (enemy_center.y > plane_center.y + offset.y) {
				collision_test.y = plane_center.y + offset.y;
			}
			if (enemy_center.y < plane_center.y - offset.y) {
				collision_test.y = plane_center.y - offset.y;
			}
			if (enemy_center.z > plane_center.z + offset.z) {
				collision_test.z = plane_center.z + offset.z;
			}
			if (enemy_center.z < plane_center.z - offset.z) {
				collision_test.z = plane_center.z - offset.z;
			}

			float distance = sqrtf(pow((collision_test.x - enemy_center.x), 2) + pow((collision_test.y - enemy_center.y), 2) + pow((collision_test.z - enemy_center.z), 2));
			if (distance <= 0.2f) {
				if (!game_over && !end_animation_started && lives > 0) {
					lives--;
					heart_blink_animation = true;
					blinking_count = 0;
				}

				if (lives == 0) {
					end_animation_started = true;
					hit_animation = false;
				}
				else {
					hit_animation_timer = -1.0f;
					hit_animation = true;
				}

				enemy.animate_break = true;
			}
		}

		if (enemy.rotation <= M_PI / 4 * 3 && enemy.break_scale < 1.0f)
			auxiliary_enemy_queue.push(enemy);
	}

	while (!auxiliary_enemy_queue.empty()) {
		EnemyInfo enemy = auxiliary_enemy_queue.front();
		auxiliary_enemy_queue.pop();
		enemy_queue.push(enemy);
	}
}

void Avion::FuelObjManager(float deltaTimeSeconds) {
	glm::vec3 plane_center = glm::vec3(plane_pos, 0);
	glm::mat4 modelMatrix;

	while (!fuel_queue.empty()) {
		FuelInfo fuel = fuel_queue.front();
		fuel_queue.pop();

		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0, -21, 0));
		modelMatrix = glm::rotate(modelMatrix, fuel.rotation, glm::vec3(0, 0, 1));
		modelMatrix = glm::translate(modelMatrix, glm::vec3(fuel.x_pos, 0, fuel.z_pos));

		
		modelMatrix = glm::rotate(modelMatrix, fuel.local_rotation, glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.05f, 0.05f, 0.05f));
		modelMatrix = glm::rotate(modelMatrix, -RADIANS(45), glm::vec3(1, 0, 0));
		modelMatrix = glm::rotate(modelMatrix, -RADIANS(45), glm::vec3(0, 1, 0));
		RenderBasic(meshes["fuel"], shaders["ShaderPlane"], modelMatrix, mapTextures["fuel_fill"], 0.75f);


		fuel.rotation += sea_rotation_speed * deltaTimeSeconds;

		if (fuel.local_rotation < 2 * M_PI) {
			fuel.local_rotation += 20 * sea_rotation_speed * deltaTimeSeconds;
		}
		else {
			fuel.local_rotation += -2 * M_PI;
			fuel.local_rotation += 20 * sea_rotation_speed * deltaTimeSeconds;
		}

		if (fuel.rotation <= M_PI / 4 + min_distance_between_entities)
			allowed_to_spawn = false;

		bool collision = false;
		if (fuel.rotation >= M_PI / 2) {
			glm::vec3 fuel_center = glm::vec3(modelMatrix[3][0], modelMatrix[3][1], modelMatrix[3][2]);
			glm::vec3 collision_test = fuel_center;
			glm::vec3 offset = glm::vec3(0.3f, 0.1f, 0.3f);
			offset = glm::mat3(glm::rotate(glm::mat4(1), plane_rotation, glm::vec3(0, 0, 1))) * offset;

			if (fuel_center.x > plane_center.x + offset.x) {
				collision_test.x = plane_center.x + offset.x;
			}
			if (fuel_center.x < plane_center.x - offset.x) {
				collision_test.x = plane_center.x - offset.x;
			}
			if (fuel_center.y > plane_center.y + offset.y) {
				collision_test.y = plane_center.y + offset.y;
			}
			if (fuel_center.y < plane_center.y - offset.y) {
				collision_test.y = plane_center.y - offset.y;
			}
			if (fuel_center.z > plane_center.z + offset.z) {
				collision_test.z = plane_center.z + offset.z;
			}
			if (fuel_center.z < plane_center.z - offset.z) {
				collision_test.z = plane_center.z - offset.z;
			}

			float distance = sqrtf(pow((collision_test.x - fuel_center.x), 2) + pow((collision_test.y - fuel_center.y), 2) + pow((collision_test.z - fuel_center.z), 2));
			if (distance <= 0.1f) {
				collision = true;
				if (!game_over && !end_animation_started && lives > 0) {
					fuel_level = min(fuel_level + 0.04f, 1.0f);
				}
			}
		}

		if (fuel.rotation <= M_PI / 4 * 3 && !collision)
			auxiliary_fuel_queue.push(fuel);
	}

	while (!auxiliary_fuel_queue.empty()) {
		FuelInfo fuel = auxiliary_fuel_queue.front();
		auxiliary_fuel_queue.pop();
		fuel_queue.push(fuel);
	}
}

void Avion::SpawnManager() {
	int should_spawn = rand() % spawn_frequency;

	if (should_spawn == 0 && allowed_to_spawn) {
		float x_pos_group = (rand() % 35) / 10.0f + 20.0f;
		float amplitude = (rand() % 60) / 100.0f - 0.3f;
		for (int i = 0; i < rand() % 6 + 2; i++) {
			FuelInfo new_fuel;
			new_fuel.rotation = M_PI / 4 - M_PI / 256 * i;
			new_fuel.local_rotation = 0.0f;
			new_fuel.x_pos = x_pos_group + amplitude * sin(-(new_fuel.rotation - M_PI/4) * 48);
			new_fuel.z_pos = 0.0;
			fuel_queue.push(new_fuel);
		}
	}

	if (should_spawn % 10 == 1 && allowed_to_spawn) {
		EnemyInfo new_enemy;
		new_enemy.rotation = M_PI / 4;
		new_enemy.animate_break = false;
		new_enemy.break_scale = 0.0f;
		new_enemy.alpha = 1.0f;
		new_enemy.local_rotation = 0.0f;
		new_enemy.x_pos = (rand() % 35) / 10.0f + 20.0f;
		new_enemy.z_pos = 0.0;
		enemy_queue.push(new_enemy);
	}

}

void Avion::UIManager(float deltaTimeSeconds) {
	if (!game_over && game_started && starting_animation_ended && !end_animation_started && deltaTimeSeconds < 1) {
		fuel_level -= 0.05f * deltaTimeSeconds;
		if (fuel_level <= 0) {
			fuel_level = 0;
			end_animation_started = true;
		}
	}

	if (game_over) {
		glm::mat4 modelMatrix = glm::mat4(1);
		RenderBasic(meshes["quad"], shaders["ShaderUI"], modelMatrix, mapTextures["game_over"]);
		RenderBasic(meshes["quad"], shaders["ShaderUI"], modelMatrix, mapTextures["game_over_text"]);
	}

	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0.75f, 0.85f, 0.0f));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f, 0.05f, 0.0f));
	RenderBasic(meshes["quad"], shaders["ShaderUI"], modelMatrix, mapTextures["fuel_margin"]);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(1.0f, 0.0f, 0.0f));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(fuel_level, 1.0f, 0.0f));
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-1.0f, 0.0f, 0.0f));
	RenderBasic(meshes["quad"], shaders["ShaderUI"], modelMatrix, mapTextures["fuel_fill"]);
	
	if (lives >= 1) {
		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.9f, 0.85f, 0.0f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.04f, 0.06f, 0.0f));
		RenderBasic(meshes["quad"], shaders["ShaderUI"], modelMatrix, mapTextures["heart"]);
	}
	else if (lives == 0 && heart_blink_animation) {
		blinking_count += 3*deltaTimeSeconds;
		if (floor(blinking_count) == 6) {
			heart_blink_animation = false;
		}
		else if ((int)floor(blinking_count) % 2 == 1) {
			modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.9f, 0.85f, 0.0f));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.04f, 0.06f, 0.0f));
			RenderBasic(meshes["quad"], shaders["ShaderUI"], modelMatrix, mapTextures["heart"]);
		}
	}

	if (lives >= 2) {
		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.8f, 0.85f, 0.0f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.04f, 0.06f, 0.0f));
		RenderBasic(meshes["quad"], shaders["ShaderUI"], modelMatrix, mapTextures["heart"]);
	}
	else if (lives == 1 && heart_blink_animation) {
		blinking_count += 3 * deltaTimeSeconds;
		if (floor(blinking_count) == 6) {
			heart_blink_animation = false;
		}
		else if ((int)floor(blinking_count) % 2 == 1) {
			modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.8f, 0.85f, 0.0f));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.04f, 0.06f, 0.0f));
			RenderBasic(meshes["quad"], shaders["ShaderUI"], modelMatrix, mapTextures["heart"]);
		}
	}

	if (lives >= 3) {
		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.7f, 0.85f, 0.0f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.04f, 0.06f, 0.0f));
		RenderBasic(meshes["quad"], shaders["ShaderUI"], modelMatrix, mapTextures["heart"]);
	}
	else if (lives == 2 && heart_blink_animation) {
		blinking_count += 3 * deltaTimeSeconds;
		if (floor(blinking_count) == 6) {
			heart_blink_animation = false;
		}
		else if ((int)floor(blinking_count) % 2 == 1) {
			modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.7f, 0.85f, 0.0f));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.04f, 0.06f, 0.0f));
			RenderBasic(meshes["quad"], shaders["ShaderUI"], modelMatrix, mapTextures["heart"]);
		}
	}

}

void Avion::AnimationManager(float deltaTimeSeconds) {
	if (game_started && !starting_animation_ended) {
		float old_plane_pos = plane_pos.y;
		plane_pos.y = 5 * sin(2 * plane_pos.x + 2) - 3.0f;

		if (old_plane_pos = plane_pos.y < 0) {
			plane_rotates_UP = true;
			plane_rotates_DOWN = false;
		}
		else {
			plane_rotates_UP = false;
			plane_rotates_DOWN = true;
		}

		if (plane_pos.x >= initial_plane_pos.x) {
			starting_animation_ended = true;
			plane_maximum_rotation = M_PI / 12;
			plane_pos.x = initial_plane_pos.x;
			if (cameraThirdPerson)
				camera->Set(glm::vec3(-5, plane_pos.y + 1.0f, 0), glm::vec3(1, -0.25f, 0), glm::vec3(0, 1, 0));
		}
		else {
			plane_pos.x += deltaTimeSeconds;
		}
	}
	if (!game_over && end_animation_started) {
		plane_maximum_rotation -= M_PI / 4 * deltaTimeSeconds;
		plane_pos.y -= 2 * deltaTimeSeconds;

		plane_maximum_rotation += M_PI/3 * deltaTimeSeconds;
		
		plane_rotates_UP = false;
		plane_rotates_DOWN = true;
		rotation_speed -= 10 * deltaTimeSeconds;
		if (rotation_speed < 0)
			rotation_speed = 0;
		
		if (plane_pos.y <= -7.0f)
			game_over = true;

		sea_rotation_speed = M_PI / 16;
		accelerating = false;
	}
	if (!game_over && hit_animation) {
		hit_animation_timer += 6 * deltaTimeSeconds;
		plane_pos.x = initial_plane_pos.x - 0.75f * (1.0f - abs(hit_animation_timer));

		if (hit_animation_timer >= 1.0f) {
			hit_animation = false;
			plane_pos.x = initial_plane_pos.x;
		}

	}
}

void Avion::OnInputUpdate(float deltaTime, int mods)
{
	float speed = 2;

	// move the camera only if MOUSE_RIGHT button is pressed
	if (debug_mode && window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float cameraSpeed = 2.0f;

		if (window->KeyHold(GLFW_KEY_W)) {
			// TODO : translate the camera forward
			camera->MoveForward(cameraSpeed * deltaTime);
		}

		if (window->KeyHold(GLFW_KEY_A)) {
			// TODO : translate the camera to the left
			camera->TranslateRight(-cameraSpeed * deltaTime);
		}

		if (window->KeyHold(GLFW_KEY_S)) {
			// TODO : translate the camera backwards
			camera->MoveForward(-cameraSpeed * deltaTime);
		}

		if (window->KeyHold(GLFW_KEY_D)) {
			// TODO : translate the camera to the right
			camera->TranslateRight(cameraSpeed * deltaTime);
		}

		if (window->KeyHold(GLFW_KEY_Q)) {
			// TODO : translate the camera down
			camera->TranslateUpword(-cameraSpeed * deltaTime);
		}

		if (window->KeyHold(GLFW_KEY_E)) {
			// TODO : translate the camera up
			camera->TranslateUpword(cameraSpeed * deltaTime);
		}
	}
	else {
		if (window->KeyHold(GLFW_KEY_UP)) {
			if (!game_over && game_started && starting_animation_ended && !end_animation_started) {
				if (cameraThirdPerson) {
					camera->TranslateUpword(-plane_pos.y);
				}
				else {
					camera->TranslateUpword(-0.25f * plane_pos.y);
				}

				plane_pos.y += 2 * deltaTime;
				plane_pos.y = min(plane_pos.y, 2.0f);

				if (plane_pos.y != 2.0f) {
					plane_rotates_UP = true;
					plane_rotates_DOWN = false;
				}

				if (cameraThirdPerson) {
					camera->TranslateUpword(plane_pos.y);
				}
				else {
					camera->TranslateUpword(0.25f * plane_pos.y);
				}
			}
		}

		if (window->KeyHold(GLFW_KEY_DOWN)) {
			if (!game_over && game_started && starting_animation_ended && !end_animation_started) {
				if (cameraThirdPerson) {
					camera->TranslateUpword(-plane_pos.y);
				}
				else {
					camera->TranslateUpword(-0.25f * plane_pos.y);
				}

				plane_pos.y -= 2 * deltaTime;
				plane_pos.y = max(plane_pos.y, -1.0f);

				if (plane_pos.y != -1.0f) {
					plane_rotates_UP = false;
					plane_rotates_DOWN = true;
				}

				if (cameraThirdPerson) {
					camera->TranslateUpword(plane_pos.y);
				}
				else {
					camera->TranslateUpword(0.25f * plane_pos.y);
				}
			}
		}
	}
}

void Avion::OnKeyPress(int key, int mods)
{
	// add key press event
	if (game_over && key == GLFW_KEY_SPACE) {
		game_over = false;
		game_started = true;
		starting_animation_ended = false;
		end_animation_started = false;
		lives = 3;
		fuel_level = 1.0f;
		plane_pos.x = -5.0f;
		rotation_speed = 10 * M_PI;
		dificulty_adjustment = 0.0f;
		while (!enemy_queue.empty())
			enemy_queue.pop();
		while (!fuel_queue.empty())
			fuel_queue.pop();
	}

	if (!game_over) {
		if(key == GLFW_KEY_C) {
			if (cameraThirdPerson) {
				camera->Set(glm::vec3(0, 1, 5), glm::vec3(0, 0, 1), glm::vec3(0, 1, 1));
				cameraThirdPerson = false;
			}
			else {
				camera->Set(glm::vec3(-5, plane_pos.y + 1.0f, 0), glm::vec3(1, -0.25f, 0), glm::vec3(0, 1, 0));
				cameraThirdPerson = true;
			}
		}
	}
}

void Avion::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Avion::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	
	if (debug_mode && window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float sensivityOX = 0.001f;
		float sensivityOY = 0.001f;

		if (window->GetSpecialKeyState() == 0) {
			// TODO : rotate the camera in First-person mode around OX and OY using deltaX and deltaY
			// use the sensitivity variables for setting up the rotation speed
			camera->RotateFirstPerson_OX(-sensivityOX * deltaY);
			camera->RotateFirstPerson_OY(-sensivityOY * deltaX);

		}
	}
	else if (!game_over && game_started && starting_animation_ended && !end_animation_started) {
		mouseY = max(mouseY, resolution.y / 4.0f);
		mouseY = min(mouseY, resolution.y / 4.0f * 3.0f);
		
		if (cameraThirdPerson) {
			camera->TranslateUpword(-plane_pos.y);
		}
		else {
			camera->TranslateUpword(-0.25f * plane_pos.y);
		}
				
		float position = resolution.y / 2.0f - (mouseY - resolution.y / 4.0f);
		position = position / (resolution.y / 2.0f);
		position = position * 3.0f - 1.0f;
		plane_pos.y = position;
		if (deltaY < 0) {
			plane_rotates_UP = true;
			plane_rotates_DOWN = false;
		}
		if (deltaY > 0) {
			plane_rotates_UP = false;
			plane_rotates_DOWN = true;
		}

		if (cameraThirdPerson) {
			camera->TranslateUpword(plane_pos.y);
		}
		else {
			camera->TranslateUpword(0.25f * plane_pos.y);
		}
	}
}

void Avion::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
	if (!game_over && !end_animation_started && starting_animation_ended && game_started) {
		sea_rotation_speed = M_PI / 8;
		accelerating = true;
	}
	
}

void Avion::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
		sea_rotation_speed = M_PI / 16;
		accelerating = false;
}

void Avion::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Avion::OnWindowResize(int width, int height)
{
}


Mesh* Avion::CreateSea(std::string name) {
	std::vector<VertexFormat> vertices;
	std::vector<unsigned short> indices;
	float angle, step = M_PI / 160;
	int i, current_starting_point = 0, number_of_points;
	const int N = 10;

	vertices.push_back(VertexFormat(glm::vec3(0, 0, 0)));
	vertices.push_back(VertexFormat(glm::vec3(0, 1, 0)));
	for (i = 2, angle = step; angle < 2 * M_PI; i++, angle += step) {
		vertices.push_back(VertexFormat(glm::vec3(sin(angle), cos(angle), 0)));
		indices.push_back(current_starting_point + 0);
		indices.push_back(current_starting_point + i);
		indices.push_back(current_starting_point + i - 1);

	}
	indices.push_back(current_starting_point + 0);
	indices.push_back(current_starting_point + 1);
	indices.push_back(current_starting_point + i - 1);

	current_starting_point += i;
	number_of_points = i;


	for (int k = 1; k < N; k++) {
		vertices.push_back(VertexFormat(glm::vec3(0, 0, -k)));
		vertices.push_back(VertexFormat(glm::vec3(0, 1, -k)));
		for (i = 2, angle = step; angle < 2 * M_PI; i++, angle += step) {
			vertices.push_back(VertexFormat(glm::vec3(sin(angle), cos(angle), -k)));

			if (k == N - 1) {
				indices.push_back(current_starting_point + 0);
				indices.push_back(current_starting_point + i - 1);
				indices.push_back(current_starting_point + i);
			}

			indices.push_back(current_starting_point + i);
			indices.push_back(current_starting_point + i - 1);
			indices.push_back(current_starting_point - number_of_points + i);

			indices.push_back(current_starting_point + i - 1);
			indices.push_back(current_starting_point - number_of_points + i - 1);
			indices.push_back(current_starting_point - number_of_points + i);
		}
		if (k == N - 1) {
			indices.push_back(current_starting_point + 0);
			indices.push_back(current_starting_point + i - 1);
			indices.push_back(current_starting_point + 1);
		}

		indices.push_back(current_starting_point + i - 1);
		indices.push_back(current_starting_point - number_of_points + i - 1);
		indices.push_back(current_starting_point - number_of_points + 1);

		indices.push_back(current_starting_point + i - 1);
		indices.push_back(current_starting_point - number_of_points + 1);
		indices.push_back(current_starting_point + 1);

		current_starting_point += i;

	}



	Mesh* mesh = new Mesh(name);
	mesh->InitFromData(vertices, indices);
	return mesh;


}

void Avion::RenderBasic(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Texture2D* texture1, float ambient_light, float alpha)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	GLint loc_time = glGetUniformLocation(shader->program, "time");
	glUniform1f(loc_time, Engine::GetElapsedTime());

	// Set shader uniforms for light & material properties
	// TODO: Set light position uniform
	GLint loc_light_position = glGetUniformLocation(shader->program, "light_position");
	glUniform3fv(loc_light_position, 1, glm::value_ptr(glm::vec3(5, 10, 5)));

	// TODO: Set eye position (camera position) uniform
	glm::vec3 eyePosition = camera->GetTargetPosition();
	GLint loc_eye_position = glGetUniformLocation(shader->program, "eye_position");
	glUniform3fv(loc_eye_position, 1, glm::value_ptr(eyePosition));

	// TODO: Set material property uniforms (shininess, kd, ks, object color)
	//float material_kd = 1;
	GLint loc_kd = glGetUniformLocation(shader->program, "material_kd");
	glUniform1f(loc_kd, 50);

	//float material_ks = 1;
	GLint loc_ks = glGetUniformLocation(shader->program, "material_ks");
	glUniform1f(loc_ks, 50);

	//int shininess = 10;
	GLint loc_shininess = glGetUniformLocation(shader->program, "material_shininess");
	glUniform1i(loc_shininess, 100);

	GLint loc_ambient = glGetUniformLocation(shader->program, "ambient_light");
	glUniform1f(loc_ambient, ambient_light);

	GLint loc_alpha = glGetUniformLocation(shader->program, "object_alpha");
	glUniform1f(loc_alpha, alpha);

	// Bind model matrix
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Bind view matrix
	glm::mat4 viewMatrix = camera->GetViewMatrix();
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// Bind projection matrix
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	if (texture1)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());
		glUniform1i(glGetUniformLocation(shader->program, "texture_1"), 0);
	}

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

void Avion::RenderSea(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix) {
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	GLint loc_time = glGetUniformLocation(shader->program, "time");
	glUniform1f(loc_time, Engine::GetElapsedTime());

	// Set shader uniforms for light & material properties
	// TODO: Set light position uniform
	GLint loc_light_position = glGetUniformLocation(shader->program, "light_position");
	glUniform3fv(loc_light_position, 1, glm::value_ptr(glm::vec3(5, 10, 5)));

	// TODO: Set eye position (camera position) uniform
	glm::vec3 eyePosition = camera->GetTargetPosition();
	GLint loc_eye_position = glGetUniformLocation(shader->program, "eye_position");
	glUniform3fv(loc_eye_position, 1, glm::value_ptr(eyePosition));

	// TODO: Set material property uniforms (shininess, kd, ks, object color)
	//float material_kd = 1;
	GLint loc_kd = glGetUniformLocation(shader->program, "material_kd");
	glUniform1f(loc_kd, 50);

	//float material_ks = 1;
	GLint loc_ks = glGetUniformLocation(shader->program, "material_ks");
	glUniform1f(loc_ks, 50);

	//int shininess = 10;
	GLint loc_shininess = glGetUniformLocation(shader->program, "material_shininess");
	glUniform1i(loc_shininess, 100);

	// Bind model matrix
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Bind view matrix
	glm::mat4 viewMatrix = camera->GetViewMatrix();
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// Bind projection matrix
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

void Avion::RenderUI(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Texture2D* texture1) {
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// Bind model matrix
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	
	if (texture1)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());
		glUniform1i(glGetUniformLocation(shader->program, "texture_1"), 0);
	}
	
	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}