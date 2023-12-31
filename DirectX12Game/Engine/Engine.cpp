#include "pch.h"
#include "Engine.h"

void Engine::Init(const WindowInfo& info)
{
	// 클라에서 사용함.
	// 초기화를 시켜줘야한다.
	// 출력 윈도우 핸들
	// 윈도우 너비, 높이, 창모드인지

	_window = info;
	ResizeWindow(_window.width, _window.height);

	// 그려질 화면 크기를 설정
	_viewport = { 0, 0, static_cast<FLOAT>(info.width), static_cast<FLOAT>(info.height), 0.0f, 1.0f };
	_scissorRect = CD3DX12_RECT(0, 0, info.width, info.height);
	// C로 시작하는게 d3dx12.h 헬퍼 클래스이다.

	_device = make_shared<Device>();
	_cmdQueue = make_shared<CommandQueue>();
	_swapChain = make_shared<SwapChain>();
	_rootSignature = make_shared<RootSignature>();
	_cb = make_shared<ConstantBuffer>();
	_tableDescriptorHeap = make_shared<TableDescriptorHeap>();

	_device->Init();
	_cmdQueue->Init(_device->GetDevice(), _swapChain);
	_swapChain->Init(info, _device->GetDevice(), _device->GetDXGI(), _cmdQueue->GetCmdQueue());
	_rootSignature->Init(_device->GetDevice());
	_cb->Init(sizeof(Transform), 256);
	_tableDescriptorHeap->Init(256);
}

void Engine::Render()
{
	RenderBegin();

	// TODO : 나머지 물체들을 그려준다

	RenderEnd();
}

void Engine::RenderBegin()
{
	_cmdQueue->RenderBegin(&_viewport, &_scissorRect);
}

void Engine::RenderEnd()
{
	_cmdQueue->RenderEnd();
}

// 창 크기를 설정하는 함수
void Engine::ResizeWindow(int32 width, int32 height)
{
	_window.width = width;
	_window.height = height;

	RECT rect = { 0, 0, width, height };
	::AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
	::SetWindowPos(_window.hwnd, 0, 100, 100, width, height, 0); // 100, 100 위치에 width, height 크기만큼 창 위치가 설정됨
}
