#pragma once

#include "Fade.h"

class Central;

/// �V�[���؂�ւ��p
class Scene {
public:
	Scene(void);
	virtual ~Scene(void);

	/**
	 * �X�V���͂��ꂾ���Ăяo��
	 */
	void method();

	/**
	 * �`��p
	 */
	virtual void draw();

protected:
	/**
	 * ������
	 */
	virtual void init();

	/**
	 * �X�V�p
	 */
	virtual void update();

	/**
	 * �㏈���p
	 */
	virtual void uninit();

private:
	/// central�N���X��ۑ����Ă���(���������Q�b�g����R�X�g�͖��ʂƔ��f)
	Central* central;
	/// state���
	unsigned int phase;
	/// fade
	Fade* fade;
};
