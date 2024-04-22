#include "pch.h"
#include "GameObject.h"
#include "Component.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "Rigidbody.h"
CollisionManager* CollisionManager::m_Pthis = nullptr;


void CollisionManager::Create()
{
	if (!m_Pthis)
	{
		m_Pthis = new CollisionManager();
		m_Pthis->m_objVec = new vector<Collider*>();
	}
}

CollisionManager* CollisionManager::GetInstance()
{
	return m_Pthis;
}

void CollisionManager::Destroy()
{
	if (m_Pthis)
	{
		delete m_Pthis->m_objVec;
		m_Pthis->m_objVec = nullptr;
		delete m_Pthis;
		m_Pthis = nullptr;
	}
}

void CollisionManager::AddCollider(Collider* col)
{
	m_objVec->push_back(col);
}

bool CollisionManager::UnregisterCollider(Collider* col)
{
	for (vector<Collider*>::iterator itr = m_objVec->begin(); itr != m_objVec->end(); itr++)
	{
		if ((*itr) == col)
		{
			m_objVec->erase(itr);
			return true;
		}
	}
	return false;
}

void CollisionManager::Update()
{
	RECT r1, r2, tmpr;
	set<Collider*> cloneColSet;
	for (vector<Collider*>::iterator itr1 = m_objVec->begin(); itr1 != m_objVec->end(); itr1++)
	{
		if (DEBUGMODE)
		{
			(*itr1)->DrawCollider();
		}
		cloneColSet = set<Collider*>((*itr1)->SetCol()->begin(), (*itr1)->SetCol()->end());
		(*itr1)->SetCol()->clear();

		r1 = { (long)(*itr1)->ColOffset().x + (long)(*itr1)->GetGameObject()->Position().x,
					(long)(*itr1)->ColOffset().y + (long)(*itr1)->GetGameObject()->Position().y,
					(long)(*itr1)->ColOffset().x + (long)(*itr1)->GetGameObject()->Position().x + (long)(*itr1)->ColSize().x,
					(long)(*itr1)->ColOffset().y + (long)(*itr1)->GetGameObject()->Position().y + (long)(*itr1)->ColSize().y };
		vector<Collider*>::iterator tmpItr = itr1;
		for (vector<Collider*>::iterator itr2 = ++tmpItr; itr2 != m_objVec->end(); itr2++)
		{
			if ((*itr1) == (*itr2))
				continue;

			r2 = { (long)(*itr2)->ColOffset().x + (long)(*itr2)->GetGameObject()->Position().x,
						(long)(*itr2)->ColOffset().y + (long)(*itr2)->GetGameObject()->Position().y,
						(long)(*itr2)->ColOffset().x + (long)(*itr2)->GetGameObject()->Position().x + (long)(*itr2)->ColSize().x,
						(long)(*itr2)->ColOffset().y +(long)(*itr2)->GetGameObject()->Position().y + (long) (*itr2)->ColSize().y };
			if (IntersectRect(&tmpr, &r1, &r2)) //충돌
			{
				(*itr1)->SetCol()->insert(*itr2);
				bool isfind = false;
				if(cloneColSet.find(*itr2) != cloneColSet.end())
					isfind = true;
				for (vector<Component*>::iterator citr = (*itr1)->GetGameObject()->GetComponentVec()->begin();
					citr != (*itr1)->GetGameObject()->GetComponentVec()->end();
					citr++)
				{
					if (!isfind) (*citr)->OnCollisionEnter((*itr2));
					else (*citr)->OnCollision((*itr2));
				}
				for (vector<Component*>::iterator citr = (*itr2)->GetGameObject()->GetComponentVec()->begin();
					citr != (*itr2)->GetGameObject()->GetComponentVec()->end();
					citr++)
				{
					if (!isfind) (*citr)->OnCollisionEnter((*itr1));
					else (*citr)->OnCollision((*itr1));
				}
			}
			else //현재 충돌이 아니고
			{
				if (cloneColSet.find(*itr2) != cloneColSet.end()) //이전 프레임에서는 충돌이었다면
				{
					for (vector<Component*>::iterator citr = (*itr1)->GetGameObject()->GetComponentVec()->begin();
						citr != (*itr1)->GetGameObject()->GetComponentVec()->end();
						citr++)
					{
						(*citr)->OnCollisionExit((*itr2));
					}
					for (vector<Component*>::iterator citr = (*itr2)->GetGameObject()->GetComponentVec()->begin();
						citr != (*itr2)->GetGameObject()->GetComponentVec()->end();
						citr++)
					{
						(*citr)->OnCollisionExit((*itr1));
					}
				}
			}
		}
	}
}

void CollisionManager::Clear()
{
	m_objVec->clear();
}
