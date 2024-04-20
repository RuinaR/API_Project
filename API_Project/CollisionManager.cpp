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
	vector<Collider*> cloneColVec;
	for (vector<Collider*>::iterator itr1 = m_objVec->begin(); itr1 != m_objVec->end(); itr1++)
	{
		if (DEBUGMODE)
		{
			(*itr1)->DrawCollider();
		}
		cloneColVec = (*(*itr1)->VecCol());
		(*itr1)->VecCol()->clear();

		r1 = { (long)(*itr1)->ColOffset().x + (long)(*itr1)->GetGameObject()->Position().x,
					(long)(*itr1)->ColOffset().y + (long)(*itr1)->GetGameObject()->Position().y,
					(long)(*itr1)->ColOffset().x + (long)(*itr1)->GetGameObject()->Position().x + (long)(*itr1)->ColSize().x,
					(long)(*itr1)->ColOffset().y + (long)(*itr1)->GetGameObject()->Position().y + (long)(*itr1)->ColSize().y };
		
		for (vector<Collider*>::iterator itr2 = m_objVec->begin(); itr2 != m_objVec->end(); itr2++)
		{
			if ((*itr1) == (*itr2))
				continue;

			r2 = { (long)(*itr2)->ColOffset().x + (long)(*itr2)->GetGameObject()->Position().x,
						(long)(*itr2)->ColOffset().y + (long)(*itr2)->GetGameObject()->Position().y,
						(long)(*itr2)->ColOffset().x + (long)(*itr2)->GetGameObject()->Position().x + (long)(*itr2)->ColSize().x,
						(long)(*itr2)->ColOffset().y +(long)(*itr2)->GetGameObject()->Position().y + (long) (*itr2)->ColSize().y };
			if (IntersectRect(&tmpr, &r1, &r2)) //Ãæµ¹
			{
				(*itr1)->VecCol()->push_back(*itr2);
				bool isfind = false;
				for (vector<Collider*>::iterator titr = cloneColVec.begin(); titr != cloneColVec.end(); titr++)
				{
					if ((*titr) == (*itr2))
					{
						isfind = true;
						break;
					}
				}
				for (vector<Component*>::iterator citr = (*itr1)->GetGameObject()->GetComponentVec()->begin();
					citr != (*itr1)->GetGameObject()->GetComponentVec()->end();
					citr++)
				{
					if (!isfind)
						(*citr)->OnCollisionEnter((*itr2));
					else
						(*citr)->OnCollision((*itr2));
				}
			}
		}
		for (vector<Collider*>::iterator itr3 = cloneColVec.begin(); itr3 != cloneColVec.end(); itr3++)
		{
			bool skip = false;
			for (vector<Collider*>::iterator itr4 = (*itr1)->VecCol()->begin(); itr4 != (*itr1)->VecCol()->end(); itr4++)
			{
				if ((*itr3) == (*itr4))
				{
					skip = true;
					break;
				}
			}
			if (!skip)
			{
				for (vector<Component*>::iterator citr = (*itr1)->GetGameObject()->GetComponentVec()->begin();
						citr != (*itr1)->GetGameObject()->GetComponentVec()->end();
						citr++)
					{
						(*citr)->OnCollisionExit((*itr3));
					}
				break;
			}
		}
	}
}

void CollisionManager::Clear()
{
	for (vector<Collider*>::iterator itr = m_objVec->begin(); itr != m_objVec->end(); itr++)
	{
		m_objVec->clear();
	}
}
