/*
 *  Win32DataChannelHandler applies mouse and keyboard messages to calculate the
 *  camera state and forwards updates to the camera state to the data channel with
 *  a JSON message containing camera position, look at position, and up vector.
 *
 *  ArcBall is used to apply orientation changes from mouse events.
 *
 *  Arrow keys and 'A' 'W' 'D' 'S' keys are used to position the camera.
 *
 *  Keyboard and Mouse events are forwarded to the data channel as JSON messages.
 */

#pragma once

#include "webrtc/base/sigslot.h"
#include "data_channel_handler.h"
#include "arc_ball.h"

class Win32DataChannelHandler : public sigslot::has_slots<>,
	public DataChannelHandler
{
public:
	Win32DataChannelHandler(DataChannelCallback* data_channel_callback);
	~Win32DataChannelHandler();

	void ProcessMessage(MSG* msg);
	void ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam);

private:
	void ResetCamera();

	int stereo_mode_;
	int width_;
	int height_;
	int keyboardTick;
	int mouseTick;
	int mouseMoveTick;
	std::unique_ptr<DirectX::Mouse> mouse_;
	DirectX::Mouse::ButtonStateTracker mouse_button_tracker_;
	ArcBall ball_camera_;
	DirectX::SimpleMath::Matrix view_;
	DirectX::SimpleMath::Vector3 camera_focus_;
	DirectX::SimpleMath::Vector3 last_camera_pos_;
	DirectX::SimpleMath::Quaternion camera_rot_;
	float zoom_;
	float distance_;
};

