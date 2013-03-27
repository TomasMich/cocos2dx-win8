/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (c) 2009      On-Core

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

// For licensing information relating to this distribution please see Third Party Notices file.

#ifndef __ACTION_CCGRID_ACTION_H__
#define __ACTION_CCGRID_ACTION_H__

#include "CCActionInterval.h"
#include "CCActionInstant.h"
NS_CC_BEGIN
	class CCGridBase;

	/** @brief Base class for Grid actions */
	class CC_DLL CCGridAction : public CCActionInterval
	{
	public:
		virtual CCObject* copyWithZone(CCZone* pZone);
		virtual void startWithTarget(CCNode *pTarget);
		virtual CCActionInterval* reverse(void);

		/** initializes the action with size and duration */
		virtual bool initWithDuration(float duration, const CCSize& gridSize);
		/** returns the grid */
		virtual CCGridBase* getGrid(void);

	public:
		/** creates the action with size and duration */
		static CCGridAction* create(float duration, const CCSize& gridSize);

	protected:
		CCSize m_sGridSize;
	};

	/** 
	 @brief Base class for CCGrid3D actions.
	 Grid3D actions can modify a non-tiled grid.
	 */
	class CC_DLL CCGrid3DAction : public CCGridAction
	{
	public:
		/** returns the grid */
		virtual CCGridBase* getGrid(void);
		/** returns the vertex than belongs to certain position in the grid */
		ccVertex3F vertex(const CCPoint& pos);
		/** returns the non-transformed vertex than belongs to certain position in the grid */
		ccVertex3F originalVertex(const CCPoint& pos);
		/** sets a new vertex to a certain position of the grid */
		void setVertex(const CCPoint& pos, const ccVertex3F& vertex);

	public:
		/** creates the action with size and duration */
        static CCGrid3DAction* actionWithSize(const CCSize& gridSize, ccTime duration);
	};

	/** @brief Base class for CCTiledGrid3D actions */
	class CC_DLL CCTiledGrid3DAction : public CCGridAction
	{
	public:
		/** returns the tile that belongs to a certain position of the grid */
		ccQuad3 tile(const CCPoint& pos);
		/** returns the non-transformed tile that belongs to a certain position of the grid */
		ccQuad3 originalTile(const CCPoint& pos);
		/** sets a new tile to a certain position of the grid */
		void setTile(const CCPoint& pos, const ccQuad3& coords);

		/** returns the grid */
		virtual CCGridBase* getGrid(void);

	public:
		/** creates the action with size and duration */
        static CCTiledGrid3DAction* actionWithSize(const CCSize& gridSize, ccTime duration);
	};

	/** @brief CCAccelDeccelAmplitude action */
	class CC_DLL CCAccelDeccelAmplitude : public CCActionInterval
	{
	public:
		virtual ~CCAccelDeccelAmplitude(void);
		/** initializes the action with an inner action that has the amplitude property, and a duration time */
		bool initWithAction(CCAction *pAction, ccTime duration);

		virtual void startWithTarget(CCNode *pTarget);
		virtual void update(ccTime time);
        virtual CCActionInterval* reverse(void);

		/** get amplitude rate */
		inline float getRate(void) { return m_fRate; }
		/** set amplitude rate */
		inline void setRate(float fRate) { m_fRate = fRate; }

	public:
		/** creates the action with an inner action that has the amplitude property, and a duration time */
		static CCAccelDeccelAmplitude* create(CCAction *pAction, ccTime duration);

	protected:
		float m_fRate;
		CCActionInterval *m_pOther;
	};

	/** @brief CCAccelAmplitude action */
	class CC_DLL CCAccelAmplitude : public CCActionInterval
	{
	public:
		~CCAccelAmplitude(void);
		/** initializes the action with an inner action that has the amplitude property, and a duration time */
		bool initWithAction(CCAction *pAction, ccTime duration);

		/** get amplitude rate */
		inline float getRate(void) { return m_fRate; }
		/** set amplitude rate */
		inline void setRate(float fRate) { m_fRate = fRate; }

		virtual void startWithTarget(CCNode *pTarget);
		virtual void update(ccTime time);
        virtual CCActionInterval* reverse(void);

	public:
		/** creates the action with an inner action that has the amplitude property, and a duration time */
		static CCAccelAmplitude* create(CCAction *pAction, ccTime duration);

	protected:
		float m_fRate;
		CCActionInterval *m_pOther;
	};

	/** @brief CCDeccelAmplitude action */
	class CC_DLL CCDeccelAmplitude : public CCActionInterval
	{
	public:
		~CCDeccelAmplitude(void);
		/** initializes the action with an inner action that has the amplitude property, and a duration time */
		bool initWithAction(CCAction *pAction, ccTime duration);

		/** get amplitude rate */
		inline float getRate(void) { return m_fRate; }
		/** set amplitude rate */
		inline void setRate(float fRate) { m_fRate = fRate; }

		virtual void startWithTarget(CCNode *pTarget);
		virtual void update(ccTime time);
        virtual CCActionInterval* reverse(void);

	public:
		/** creates the action with an inner action that has the amplitude property, and a duration time */
        static CCDeccelAmplitude* create(CCAction *pAction, ccTime duration);

	protected:
		float m_fRate;
		CCActionInterval *m_pOther;
	};

	/** @brief CCStopGrid action.
	 @warning Don't call this action if another grid action is active.
	 Call if you want to remove the the grid effect. Example:
	 CCSequence::actions(Lens::action(...), CCStopGrid::action(...), NULL);
	 */
	class CC_DLL CCStopGrid : public CCActionInstant
	{
	public:
		virtual void startWithTarget(CCNode *pTarget);

	public:
		/** Allocates and initializes the action */
		static CCStopGrid* create(void);
	};

	/** @brief CCReuseGrid action */
	class CC_DLL CCReuseGrid : public CCActionInstant
	{
	public:
		/** initializes an action with the number of times that the current grid will be reused */
        bool initWithTimes(int times);

		virtual void startWithTarget(CCNode *pTarget);

	public:
		/** creates an action with the number of times that the current grid will be reused */
		static CCReuseGrid* create(int times);

	protected:
		int m_nTimes;
	};

NS_CC_END

#endif // __ACTION_CCGRID_ACTION_H__
