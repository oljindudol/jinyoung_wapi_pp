#pragma once

//1페이즈 몬스터
//1.창조의 아이온
#include "ion.h"

//2.파괴의 얄다바오트
#include "yalda.h"

//3.사슬 공격 몬스터(자체애니메이션,컬라이더 없음)
#include "rulemon11.h"

//4.감자 공격 소환 몬스터(자체애니메이션,컬라이더 없음)
#include "rulemon12.h" 

//5.감자 몬스터 , 몬스터화 이유:땅에닿았을때 상태변화
//30개정도 몬스터풀에 넣어둠
#include "CDarkFalling.h" 


//2페이즈 몬스터
// 1.검은마법사
#include "CBlackMage2.h"

// 2.모닝스타폴 5~7개정도 풀에넣어둠
//#include "CMorningStarFall.h"
// 사슬,감자몬스터 돌려쓰기
// rulemon11.h , rulemon12.h ,CDarkFalling.h

// 3. 권능 몬스터 
//왼쪽,오른쪽,가운데는 state전환형식
//몬스터화이유 : 상태변화형태가 생산성이 좋음
//#include "powermon2.h" 


//3페이즈 몬스터
// 1. 검은마법사
//#include "CThirdBM"
// 감자몬스터 돌려쓰기
// 레이저는 검은마법사가 소환하는 스킬형식

// 2. 아랫권능 , 몬스터화 이유:땅에닿았을때 상태변화
//#include "powermon3-1.h" 

// 3. 윗권능  , 몬스터화 이유:아랫권능과의 일관성
//#include "powermon3-2.h" 


//4페이즈 몬스터
// 1. 검은마법사
//#include "CFourthBM"
//권능, 폭탄, 총알은 스킬화 (시간지나면 사라지기때문)


//5페이즈 몬스터
// 1. 창세의알 (보상상자)
//#include "CGenesisEgg"
