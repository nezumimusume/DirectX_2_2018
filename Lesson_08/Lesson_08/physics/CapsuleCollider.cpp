/*!
 * @brief	�J�v�Z���R���C�_�[�B
 */

#include "stdafx.h"
#include "Physics/CapsuleCollider.h"



/*!
	* @brief	�f�X�g���N�^�B
	*/
CapsuleCollider::~CapsuleCollider()
{
	delete shape;
}