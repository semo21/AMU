# Backlog

주간 계획에 아직 편입되지 않은 작업 목록. 주간 계획을 세울 때 여기서 골라 Weekly Goals로 옮기고, 옮긴 항목은 삭제한다.

## 구조 / 리팩터

- SaveManager LoadProgress 가드 정리 (2026-11-23)
  - Initialize에서 SaveGameObject를 항상 생성하므로 LoadProgress의 `if (SaveGameObject)` 가드는 절대 실패하지 않음
  - bool 반환이 항상 true라 호출부의 실패 분기가 죽은 코드, 같은 파일의 Save 함수들은 가드가 없어 일관성도 없음
- Clicker 시작 흐름을 OnWorldBeginPlay로 이전 (2026-11-23)
  - 현재는 ClickerGameMode::BeginPlay가 StartWorld를 직접 호출
  - OnWorldBeginPlay는 GameMode BeginPlay보다 먼저 실행되므로, UI 바인딩 -> 경제 시작 -> HUD 초기화 순서를 함께 재설계해야 함
- DefenseEconomySubsystem Settings 가드를 Initialize의 checkf로 통일 (2026-11-25)
  - 현재 CalculateSettlementReward에서 사용할 때마다 `? : 0.0`으로 가드, ClickerEconomySubsystem은 로드 시점에 checkf 한 번으로 처리
- ClickerGameMode::BeginPlay 가드 정리 (2026-11-26)
  - `if (!ensure(...)) return;` 3개 제거, Clicker 서브시스템과 PC는 ClickerGameMode 월드에서 항상 존재
  - PC 캐스트는 CastChecked로 교체
- ActionButton 자립화 (2026-11-21)
  - 태그는 WBP에서 지정, PlayerController는 GetOwningPlayer로 획득, Registry는 GlobalUISubsystem이 소유
  - 호출부가 PC / Registry를 넘겨주는 InitializeButton 제거
- 에셋 재저장 후 CoreRedirects 정리 (2026-11-21)
  - 모듈 분리 이후 에셋을 재저장하면 DefaultEngine.ini의 Package / Class / Struct / Enum Redirects 제거 가능
  - ActiveGameNameRedirects 정리 포함

## 세이브 / 재화

- Clicker 특수 대상(황금 고블린류) (2026-11-27)
  - 일정 확률로 등장, 클릭 시 Global 재화를 직접 지급 (교환이 아닌 별도 원천, 방치 수익과 무관)
  - 지급은 AddGlobalCurrency 경로 사용, 등장 확률 / 보상은 Settings DA
- Clicker 교환 UI를 상점 탭으로 이동 (2026-11-27)
  - 현재 교환은 HUD 버튼, 로직(경제 서브시스템)은 그대로 두고 버튼 위치만 상점 UI로 옮김

- 세이브 버전 필드 추가 (SaveVersion) (2026-11-21)
  - 스냅샷 구조가 바뀌어도 이전 세이브를 판별하고 마이그레이션할 수 있도록
- AddGlobalCurrency 입력 검증 (2026-11-21)
  - 음수 / 비정상 값 지급 방지
- Global 재화 저장 방식 검토 (2026-11-21)
  - 현재 재화 변경마다 동기 저장, 자주 버는 장르가 붙으면 끊김 가능

## 에셋 / 버전관리

- 직접 제작 Content 추적 범위 확대 (2026-11-21)
  - Levels, \_\_ExternalActors\_\_, \_\_ExternalObjects\_\_, Art, Audio 중 직접 제작한 것

## 문서

- 문서 개편 (2026-11-22)
  - game_design, architecture_overview, system_* 를 현재 구조(장르 허브, 모듈 분리) 기준으로 갱신
  - api_reference를 사용 가이드로 재구성, 상세 설명은 헤더 `/** */` 주석으로 이동
  - test_cases를 PIE 회귀 테스트 체크리스트로 전환
