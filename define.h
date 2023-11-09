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
	BACKGROUND,
	TILE,
	PLATFORM,
	PLATFORM_DEBUG,
	WALL,
	PLAYER,
	MONSTER,
	PLAYER_SKILL,
	PLAYER_PJ,
	MONSTER_PJ,
	FALL_OBJ,
	PORTAL,
	WORLD_STATIC,

	UI = 29,
	CUT_SCENE =30,
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
	STATUS_BAR_POINT,
	CHARATER_NAMETAG,
	LEVEL_ALERT,
	ACHIVEMENT,
	DEBUG_TAB,
	END_ROLL,

	FONT_END,
};



enum PEN_TYPE
{
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
	START_LEVEL,
	PLAY_LEVEL,
	EDITOR_LEVEL,
	END,
};


enum class ENORMAL_MON_STATE
{
	IDLE,
	TRACE,
};

enum class PLAYER_STATE
{
	IDLE	,
	MOVE    ,
	ON_AIR	,
	DOWN	,
	ATT_NM	,
	ATT_SP	,
	ATT_HX	,
	ROPE    ,
	DEAD	,
};


enum ORIENTATION
{
	ORT_LEFT,
	ORT_RIGHT,
};


enum class DEBUFF
{
	STUN,

	NONE,
};