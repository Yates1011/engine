#include "TimedMoveAction.h"
#include "../Objects/Object.h"
#include "../Helpers/Math.h"

namespace star
{
	TimedMoveAction::TimedMoveAction(
		float32 seconds,
		const vec2 & target
		)
		: TimedAction(seconds)
		, m_Direction(0, 0)
		, m_Target(target)
		, m_StartPosition(0,0)
		, m_Speed(0)
		, m_CurrentSeconds(0)
		, m_StartPosSet(false)
	{

	}

	TimedMoveAction::TimedMoveAction(
		const tstring & name,
		float32 seconds,
		const vec2 & target
		)
		: TimedAction(name, seconds)
		, m_Direction(0, 0)
		, m_Target(target)
		, m_StartPosition(0,0)
		, m_Speed(0)
		, m_CurrentSeconds(0)
		, m_StartPosSet(false)
	{

	}

	TimedMoveAction::TimedMoveAction(
		float32 seconds,
		const vec2 & direction,
		float32 speed
		)
		: TimedAction(seconds)
		, m_Direction(direction)
		, m_Target(0, 0)
		, m_StartPosition(0,0)
		, m_Speed(speed)
		, m_CurrentSeconds(0)
		, m_StartPosSet(false)
	{

	}

	TimedMoveAction::TimedMoveAction(
		const tstring & name,
		float32 seconds,
		const vec2 & direction,
		float32 speed
		)
		: TimedAction(name, seconds)
		, m_Direction(direction)
		, m_Target(0, 0)
		, m_StartPosition(0,0)
		, m_Speed(speed)
		, m_CurrentSeconds(0)
		, m_StartPosSet(false)
	{

	}

	TimedMoveAction::~TimedMoveAction()
	{

	}

	void TimedMoveAction::Initialize()
	{
		if(!m_StartPosSet)
		{
			m_StartPosition = m_pParent->GetTransform()->GetWorldPosition().pos2D();
			m_StartPosSet = true;
		}
		m_Callback = [&] () 
		{
			if(m_Speed == 0.0f)
			{
				m_pParent->GetTransform()->Translate(m_Target);
			}
		};

		TimedAction::Initialize();
	}

	void TimedMoveAction::Update(const Context & context)
	{
		vec2 curPos = m_pParent->GetTransform()->GetWorldPosition().pos2D();
		float32 dt = float32(context.mTimeManager->GetSeconds());
		if(m_Speed == 0.0f)
		{
			m_CurrentSeconds += dt;
			m_pParent->GetTransform()->Translate(
				Lerp<vec2>(m_StartPosition, m_Target, m_CurrentSeconds / m_Seconds)
				);
		}
		else
		{
			m_pParent->GetTransform()->Translate(
				curPos + m_Direction * m_Speed * dt
				);
		}
	}

	void TimedMoveAction::SetStartPosition(const vec2 & pos)
	{
		m_StartPosition = pos;
		m_StartPosSet = true;
	}

	void TimedMoveAction::Restart()
	{
		m_pParent->GetTransform()->Translate(m_StartPosition);
		m_CurrentSeconds = 0;
	}
}