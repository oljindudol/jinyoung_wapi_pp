#pragma once


#define SINGLETON(ClassType) public:\
								static ClassType* GetInst()\
								{\
									static ClassType inst;\
									return &inst;\
								}\
							 public:\
								 ClassType* operator = (const ClassType& _Origin) = delete;\
							 private:\
								 ClassType();\
								 ClassType(const ClassType& _Origin) = delete;\
							 	 ~ClassType();

#define KEY_CHECK(Key, State) CKeyMgr::GetInst()->GetKeyState(Key) == State

#define KEY_TAP(Key) KEY_CHECK(Key, TAP)
#define KEY_PRESSED(Key) KEY_CHECK(Key, PRESSED)
#define KEY_RELEASED(Key) KEY_CHECK(Key, RELEASED)
#define KEY_NONE(Key) KEY_CHECK(Key, NONE)

#define DT	CTimeManager::GetInst()->GetDeltaTime()

#define PI	3.14159265348979f


#define GAME_FOLDER MyGame


#define GENERATED_OBJECT(type) typedef type Super;\

#define DEBUG_RENDER CEngine::GetInst()->DebugRender()
#define SELECT_PEN(DC, TYPE) FSelectPen tempPenSelect(DC, TYPE)
#define SELECT_BRUSH(DC, hBrush) FSelectBrush tempBrushSelect(DC, hBrush)
#define SELECT_FONT(DC, TYPE) FSelectFont tempFontSelect(DC, TYPE)
#define SELECT_FONT2(DC, TYPE) FSelectFont tempFontSelect2(DC, TYPE)
#define SELECT_FONT3(DC, TYPE) FSelectFont tempFontSelect3(DC, TYPE)

#define firstmon_attack2_dist 600.f


#define TILE_SIZE 64

#define CLONE(type) virtual type* Clone() {return new type(*this);}
#define CLONE_DISABLE(type) virtual type* Clone() {return nullptr;}


// Key Value
enum KEY
{
	_0,
	_1,
	_2,
	_3,
	_4,
	_5,
	_6,
	_7,
	_8,
	_9,

	NUM0,
	NUM1,
	NUM2,
	NUM3,
	NUM4,
	NUM5,
	NUM6,
	NUM7,
	NUM8,
	NUM9,

	Q,
	W,
	E,
	R,
	T,
	Y,
	U,
	I,
	O,
	P,

	A,
	S,
	D,
	F,
	G,
	H,
	J,
	K,
	L,

	Z,
	X,
	C,
	V,
	B,
	N,
	M,

	TAB,
	LSHIFT,
	LALT,
	LCTRL,
	SPACE,

	ESC,
	ENTER,
	BACK,

	LEFT,
	RIGHT,
	UP,
	DOWN,

	LBTN,
	RBTN,

	PAGE_UP,
	PAGE_DOWN,

	HOME,
	F1,
	F2,
	F3,
	F4,
	F5,
	F6,
	F7,
	F8,
	F9,
	F10,
	F11,
	F12,
	GRAVE,

	KEY_END,
};

enum KEY_STATE
{
	NONE,
	TAP,
	PRESSED,
	RELEASED,
};

enum LAYER
{
	DEFAULT,
	//WALL_FOR_COL,
	BACKGROUND,
	TILE,
	PLATFORM,
	PLATFORM_DEBUG,
	WALL,
	WALL_FOR_COL,
	MONSTER,
	MONSTER_PJB,
	NPC,
	MOUSE_COL,
	PLAYER,
	ITEM,
	PLAYER_PJ,
	PLAYER_SKILL,
	MONSTER_POWER,
	MONSTER_PJ,
	FALL_OBJ,
	PORTAL,
	WORLD_STATIC,

	UI = 29,
	CUT_SCENE = 30,
	SUPER_UI = 31,
	END = 32,
};


enum TASK_TYPE
{
	// Param1 : Layer Type, Param2 : Object Adress
	CREATE_OBJECT,

	// Object Adress
	EXPEL_OBJECT,

	// Param1 : Object Adress
	DELETE_OBJECT,

	// Param1 : LEVEL_TYPE
	LEVEL_CHANGE,
};

enum FONT_TYPE
{
	LOG_TEXT,
	STATUS_BAR_NAME,
	QUEST_DIALOG,
	STATUS_BAR_POINT,
	UPPER_BAR_PERCENT,
	CHARATER_NAMETAG,
	LEVEL_ALERT,
	ACHIVEMENT,
	DEBUG_TAB,
	END_ROLL,
	STATUS_DEBUG,
	DEBUG_MENU,

	FONT_END,
};




enum PEN_TYPE
{
	BK_PEN,
	WT_PEN,
	YELLOW_PEN,
	GREEN_PEN,
	BLUE_PEN,
	RED_PEN,

	PEN_END,
};


enum LOG_LEVEL
{
	LOG,
	WARNING,
	ERR,
};


enum class LEVEL_TYPE
{
	//START_LEVEL,
	//EDITOR_LEVEL, 
	PHASE_ZERO,			//0
	PHASE_FIRST,		//1
	PHASE_SECOND,		//2
	PHASE_THIRD,		//3
	//PHASE_FOURTH,		//4
	PHASE_FIFTH,		//5
	END,
};

enum class ENPC_STATE
{
	NONE,
	HAVE_QUEST,
	ON_QUEST,
	COMPLETE_QUEST,
	END,
};

enum class ENORMAL_MON_STATE
{
	REGEN,
	MOVE,

	IDLE,
	DIE,

	//모닝스타폴,모닝스타폴 ,총알패턴1
	ATTACK1,
	//파멸의눈  ,레이저     ,총알패턴2
	ATTACK2,
	//녹스		,끌기		,총알패턴3
	ATTACK3,
	//암흑	    ,차기		,속성폭탄
	ATTACK4,

	POWER1,
	POWER2,
	POWER3,

	BIND,
	DEBUG,
};

enum class PLAYER_STATE
{
	IDLE,
	MOVE,
	ON_AIR,
	DOWN,
	ATT_NM,
	ATT_SP,
	ATT_HX,
	ROPE,
	DEAD,
};


enum class ITEM_STATE
{
	ON_AIR,
	ON_GROUND,
	ABSORBING,
};

enum ORIENTATION
{
	ORT_LEFT,
	ORT_RIGHT,
};


enum class DEBUFF
{
	//버프:낙하물무시
	DARKSITE,
	//버프:무적
	INVINCIBLE,

	//피격 깜빡임
	ON_DAMAGED,
	//창조의 저주
	CREATION,
	//파괴의 저주
	DESTUCTION,
	//암흑
	BLIND,
	//봉인
	INABILITY,
	//슬로우
	SLOW,
	//스턴
	//STUN,
	//혼란
	//CHAOS,
	//빗나감
	//RICOCHET,
	//스킬 디버프 속성없음
	NONE,
	END,
};