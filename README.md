# Title

## 클래스 설명

#### 싱글톤 패턴
싱글톤 패턴
###### Manager : 관리자
- Game Manager : 전반적인 흐름 관리, 매니져 관리, 게임 상태, 오브젝트 관리
- Resource Manager : 이미지 리소스 관리(저장 및 호출)
- Input Manager : 사용자 입력 처리
- Scene Manager : 씬 변경, 배경 및 오브젝트 로드
- Collision Manager : 오브젝트간 충돌 처리
###### Factory
- Factory : 오브젝트 생성(게임 매니져, 씬 매니져에게 오브젝트 등록)

#### 오브젝트
Actor : 오브젝트와 동일. 
<br>위치 정보, 사이즈, 이미지, 렌더 레이어, 컴포넌트 보유
- Pawn
<br>다채로운 움직임을 보유한 오브젝트
<br>Collider, Physics 컴포넌트 보유, Move Force 와 Physics 를 통해 움직임 설정
    - Player
    <br>플레이어의 움직임 상호작용
    <br>상태(바라보는 방향, 동작 상태) 보유, 애니메이션 적용(=> Animator Component 로 빼기)
    - Enemy(미구현)
    <br>적이 보유해야 하는 기본 정보를 가진 상위 클래스
- Terrain
<br>월드 오브젝트
<br>Collider Component 보유    
    - Wall
    <br>다른 오브젝틑의 통행을 전적으로 차단
    - Ground
    <br>다른 오브젝틑의 통행을 전적으로 차단
    
    - Thin Ground
    <br>아래에서 접근하는 물체에 대해서는 통과 허용(위에서 접근하는 움직임만 차단)
        - Moving Ground
        <br>기본적인 반복 움직임만 구현
        <br>복잡한 움직임 상호작용이 필요하면 physics component 추가
- Background
<br>단순히 배경을 그리기 위한 클래스, 상호작용 없음
<br>필요시 Main Camera 를 추가할 경우 수정
    - Foreground(미구현 요소)
- Bullet
<br>공격 및 피격에 효과를 갖는 오브젝트
<br>Collider, physics 보유, 근접 공격의 경우는?
    - Player Bullet
    - Enemy Bullet

#### 컴포넌트
Component
<br>오브젝트의 구성 요소
- Collider
<br>충돌체, 위치 정보 보유(하위 클래스에서 범위를 설정), 하위 클래스 오버라이드를 통해 충돌 대상에 따른 충돌처리 가능케 함
    - Circle Collider
    <br>원형 충돌체
    - Rectanglge Collider
    <br>사각형 충돌체
- Physics
<br>물리 법칙 설정, 중력, 움직임(가속, 감속), 질량 설정

#### 씬
- Test : 단위 테스트 진행
- Main Menu : 게임 시작(스테이지 선택), 게임 종료 버튼
- Arena : 전장
- Game Over : 게임 오버 시 [Score 출력 || 메인 메뉴로 이동 || 리스타트 ]

#### UI
- Main Menu, Game Over 에서의 선택지
- Arena 에서의 체력 정보, 시간 정보
    - 적 체력 중하단, 플레이어 체력 좌측 상단 표시


