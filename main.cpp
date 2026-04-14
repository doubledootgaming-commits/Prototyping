#include "globals.h"
#include "physics.h"

struct appMain {
	bool Running = true;
	bool Debug = true;

	SDL_Renderer* Renderer;
	SDL_Window* Window;
	SDL_GPUDevice* GPU;
	SDL_GPUGraphicsPipeline* pipeline;
	SDL_Event Event{};
	appMain() {
		SDL_InitSubSystem(SDL_INIT_VIDEO && SDL_INIT_AUDIO);
		Window = SDL_CreateWindow("Prototyping", 480, 480, NULL);
		assert(Window != NULL);
		GPU = SDL_CreateGPUDevice(SDL_GPU_SHADERFORMAT_SPIRV, Debug, NULL);
		assert(GPU != NULL);
		SDL_ClaimWindowForGPUDevice(GPU, Window);
		Renderer = SDL_CreateRenderer(Window, NULL);
		assert(Renderer != NULL);

		SDL_GPUShader* TEST{};
		SDL_GPUShader* TEST2{};

		//BELOW IS TESTING
		void* code{};

		size_t size{};
		code = SDL_LoadFile("shader.spv.vert", &size);

		SDL_GPUShaderCreateInfo Info = {
			.code_size = size,
			.code = (const Uint8*)code,
			.entrypoint = "main",
			.format = SDL_GPU_SHADERFORMAT_SPIRV,
			.stage = SDL_GPU_SHADERSTAGE_VERTEX,
			.props = 0
		};
		TEST = SDL_CreateGPUShader(GPU, &Info);

		code = SDL_LoadFile("shader.spv.frag", &size);
		SDL_GPUShaderCreateInfo Info2 = {
			.code_size = size,
			.code = (const Uint8*)code,
			.entrypoint = "main",
			.format = SDL_GPU_SHADERFORMAT_SPIRV,
			.stage = SDL_GPU_SHADERSTAGE_FRAGMENT,
			.props = 0
		};
		TEST2 = SDL_CreateGPUShader(GPU, &Info2);
		SDL_free(code);
		//END

		SDL_GPUColorTargetDescription colorDesc = {
			.format = SDL_GetGPUSwapchainTextureFormat(GPU, Window)
		};
		SDL_GPUGraphicsPipelineCreateInfo PipelineInfo = {
			.vertex_shader = TEST,
			.fragment_shader = TEST2,
			.primitive_type = SDL_GPU_PRIMITIVETYPE_TRIANGLELIST,
			.target_info = {
				.color_target_descriptions = &colorDesc,
				.num_color_targets = 1
			}
		};
		
		pipeline = SDL_CreateGPUGraphicsPipeline(GPU, &PipelineInfo);
		SDL_GetError();
		
		SDL_ReleaseGPUShader(GPU, TEST);
		SDL_ReleaseGPUShader(GPU, TEST2);
	}
	~appMain() {
		SDL_DestroyGPUDevice(GPU);
		SDL_DestroyRenderer(Renderer);
		SDL_DestroyWindow(Window);
	}

	void mainLoop() {
		Vector2 p = {16, 8};
		std::println("{}", p);
		while(Running) {
			fps();
			while (SDL_PollEvent(&Event)) {
				if (Event.type == SDL_EVENT_QUIT) {
					Running = false;
				}
				if (Event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
					std::cout << "Click!" << '\n';
				}
			}
			//Rendering shit
			SDL_GPUCommandBuffer* cBuffer = SDL_AcquireGPUCommandBuffer(GPU);
			SDL_GPUTexture* swapchainTex;
			SDL_WaitAndAcquireGPUSwapchainTexture(cBuffer, Window, &swapchainTex, NULL, NULL);
			SDL_GPUColorTargetInfo ColorTarget = {
				.texture = swapchainTex,
				.clear_color = {0.0f, 0.2f, 0.4f, 1.0f},
				.load_op = SDL_GPU_LOADOP_CLEAR,
				.store_op = SDL_GPU_STOREOP_STORE
				};
			SDL_GPURenderPass* render_pass = SDL_BeginGPURenderPass(cBuffer, &ColorTarget, 1, NULL);

			SDL_BindGPUGraphicsPipeline(render_pass, pipeline);

			SDL_DrawGPUPrimitives(render_pass, 3, 1, 0, 0);

			SDL_EndGPURenderPass(render_pass);
			SDL_SubmitGPUCommandBuffer(cBuffer);
		}
	}
	void update() {
		
	}
	void fps() {//something about vulkan might be locking this to 120 max
		static Uint64 lastPoll{};
		static Uint32 FPS{};
		static Uint64 ticks{};

		FPS++;
		ticks = SDL_GetTicks();
		if (ticks > lastPoll + 1000) {
			std::string title = "Prototyping : " + std::to_string(FPS);
			SDL_SetWindowTitle(Window, title.c_str());
			lastPoll = ticks;
			FPS = 0;
		}
	}
};

int main(int argc, char* argv[]) {
	std::cout << "Hello, World!" << '\n';
	
	//appMain main;
	//main.mainLoop();

	return 0;
}