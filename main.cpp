// #include "raylib.h"
// #include "raymath.h"

// #include "imgui.h"
// #include "rlImGui.h"
// #include "rlImGuiColors.h"

// bool Quit = false;

// bool ImGuiDemoOpen = false;

// int main(int argc, char* argv[])
// {
// 	// Initialization
// 	//--------------------------------------------------------------------------------------
// 	int screenWidth = 1280;
// 	int screenHeight = 720;

// 	SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
// 	InitWindow(screenWidth, screenHeight, "ImGui Demo");
// 	SetTargetFPS(60);
// 	rlImGuiSetup(true);

//     // Windows can only be dragged from title bar
// 	ImGui::GetIO().ConfigWindowsMoveFromTitleBarOnly = true;

// 	ImageViewer.Setup();
//     ImageViewer.Open = true;

//     SceneView.Setup();
//     SceneView.Open = true;

// 	// Main game loop
// 	while (!WindowShouldClose() && !Quit)    // Detect window close button or ESC key
// 	{
// 		// ImageViewer.Update();
//         // SceneView.Update();

// 		BeginDrawing();
// 		ClearBackground(DARKGRAY);

// 		rlImGuiBegin();
// 		DoMainMenu();

// 		if (ImGuiDemoOpen)
// 			ImGui::ShowDemoWindow(&ImGuiDemoOpen);

// 		if (ImageViewer.Open)
//             ImageViewer.Show();

//         if (SceneView.Open)
//             SceneView.Show();

// 		rlImGuiEnd();

// 		EndDrawing();
// 		//----------------------------------------------------------------------------------
// 	}
// 	rlImGuiShutdown();

//     ImageViewer.Shutdown();
//     SceneView.Shutdown();

// 	// De-Initialization
// 	//--------------------------------------------------------------------------------------   
// 	CloseWindow();        // Close window and OpenGL context
// 	//--------------------------------------------------------------------------------------

// 	return 0;
// }

#include "Application.h"

int main()
{
    Application app;
    app.run();

    return 0;
}