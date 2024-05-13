#pragma once

#include "../libgl/AnimationController.h"
#include "../libgl/GLApplication.h"
#include "../libgl/OmniLight.h"
#include "../libgl/RotationController.h"
#include "Picture.h"
#include "SkyBox.h"

class CMyApplication : public CGLApplication
{
public:
	CMyApplication(const char* title, int width, int height);

protected:
	virtual void OnInit();
	virtual void OnDisplay();
	virtual void OnIdle();
	virtual void OnReshape(int width, int height);
	virtual void OnMouse(int button, int state, int x, int y);
	virtual void OnMotion(int x, int y);
	virtual void OnKeyboard(unsigned char key, int x, int y);

private:
	// Рисуем космос
	void DrawSkyBox() const;
	// Рисуем основную картину
	void DrawPicture();
	// Угол обзора по вертикали
	static const double FIELD_OF_VIEW;

	// Расстояние до ближней и дальней плоскостей отсечения
	static const double ZNEAR;
	static const double ZFAR;

	// Режим визуализации граней
	// (переключается при помощи клавиши Пробел)
	GLenum m_polygonMode;

	CRotationController m_rotationController;
	CAnimationController m_animationController;

	COmniLight m_light;

	CPicture m_picture;
	CSkyBox m_skyBox;
	bool m_animate;
};
