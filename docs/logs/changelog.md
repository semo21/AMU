```
ChangeLog.md

ChangeLog format

## Date

### feature

- 기능 구현

### fix

- 문제 해결

### refactor

- 내부 구조 개선

### perf

- 성능/메모리 개선

### docs

- 문서 변경

### chore

- 빌드, 도구, 세팅 등 기타 작업
```

## 06.12.25.

### fix(build, ui)

- 에디터 재시작 후 Actor 메시 사라짐 문제
- 업그레이드 비용 텍스트 표기
- 업그레이드 비용 텍스트 포맷 수정

## 06.16.25.

### feature(ui)

- 클릭 플로팅 텍스트 및 애니메이션 추가

## 06.26.25.

### feature(fx, ui)

- 클릭 Niagara FX 적용
- HUD 로직 리팩터 시작.

## 07.02.25.

### feature(save)

- Save/Load 시스템 추가

### refactor(architecture)

- MyPlayerController 리팩터 완료

### chore(git)

- feature/currency-persistence 브랜치 생성

## 07.04.25.

### feature(save)

- 종료시 자동 저장 구현
- SaveManagerSubsystem 도입

## 07.07.25.

### feature(save)

- 일정시간 경과시 자동저장 구현

# 07.11.25

### feature(economy)

- 오프라인 보상 추가

### fix(syntax)

- IdleRewardTextWidget 문법 오류 수정

## 07.15.25.

### feature(ui)

- IdleRewardTextWidget + 애니메이션 추가

### fix(ui)

- Widget관련 BP오류 해결

## 07.22.25.

### feature(ui)

- Offline Reward Text 추가
- 애니메이션 개선

## 07.24.25.

### refactor(ui)

- 오브젝트 풀링 구현 시작

### chore(git)

- 오브젝트 풀링 전용 브랜치 생성
- 완료된 currency-persistence 브랜치 정리

## 07.25.25.

### feature(ui)

- IdleRewardText 풀링 기반 비주얼 이펙트 구현

## 07.29.25.

### feature(ui)

- Idle 위젯 풀링 완료
- 사운드 시스템 핵심 구현
- 오디오 패키지 추가

## 08.12.25.

### refactor(system)

- UE5 상속/구조 이해 심화
  - 설계 조정 및 새 구조 스케치

## 08.15.25.

### refactor(system)

- GameManager 제거
- UISubsystem, EconomySubsystem 생성
- economySnapshot 구조체 생성
- ClickerComponent, PlayerController, SaveSubsystem 리팩터 완료.

## 08.20.25.

### fix(boot)

- 초기화/크래시 원인 해결 진행
  - UISattings DataAsset 생성 후 에셋 주입 정리

## 08.22.25.

### fix(ui, input)

- 심각한 오작동 원인 파악 및 수리 계획 수립
  - 핵심 코드 누락 확인
  - 코어 UI/Input 코드 보강

## 08.25.25.

### fix(boot, ui, save)

- Assertion 크래시 해결.
  - Save, Binaries, Intermediate폴더 삭제 후 generate VS files, 에디터 rebuild.
- Idle Reward 텍스트 누락 복구.
- Save/Load 이슈 식별

## 08.26.25.

### fix(boot, save)

- Assertion 재발
  - 지난번과 같은 방법으로 즉시 해결
  - \+ VS솔루션 빌드 진행
- Save 시스템 오류 추적

## 08.28.25.

### refactor(system)

- 구조 리팩터 완료

### fix(save, ui)

- Save time 초기화 에러 해결
- UI 업데이트 이슈 발견

## 09.02.25.

### fix(boot)

- Assertion 크래시 재발
  - 유령 BPGC 캐시로 추정
  - 이전과 같은 방법으로 해결

### chore(flow)

- 전체 게임 시스템 정상 동작 확인

## 09.03.25.

### fix(ui)

- IdleRewardText 경고 원인 규명
  - Viewport에 남아있는 인스턴스 Re-Add가 원인
  - 코드 수정 스케치

### docs

- 개발 로그, 기획 등 추가 문서 세분화 및 세부 작성 계획

  - docs
    - design
      - system
        - system_economy.md
        - system_ui.md
      - game_design.md(GDD)
    - diary
      - devlog.md(ex. DevelopmentLog.md)
    - logs
      - changelog.md
    - planning
      - Daily
      - Weekly
      - backlog.md
      - roadmap.md
    - release
    - tech
      - api_reference.md
      - architecture_overview.md
    - testing

- 이후 필요 시 추가/생성 예정

## 09.05.25.

### docs

- 기존 Devlog내용을 바탕으로 ChangeLog 내용 추가.

---

> 2025.09.06 이후로는 일자별 기록 대신 릴리즈 단위로 기록함.

## v0.2-genre-hub (2025.12.30 ~ 2026.11.22)

### feature(lobby, level)

- Lobby 레벨, 캐릭터 베이스, 포탈 상호작용 구현
- 레벨 전환 구현 (Lobby ↔ Clicker, Lobby ↔ Defense)
- 레벨별 UI Subsystem 구조 도입
- GameMode 기준으로 생성되는 World Subsystem 베이스 추가

### feature(global)

- GlobalEconomySubsystem (공용 재화), GlobalProgressSubsystem (레벨 해금 진행도) 추가
- UPlayerSaveGame 기반 통합 세이브 (공용 데이터 + 레벨별 스냅샷)
- Level.Lobby 기본 해금, 초기 해금 레벨 및 해금 가격 DataAsset화
- 공용 재화 지출(TrySpendGlobalCurrency), 레벨 해금 시도(TryUnlockLevel) 추가
- 포탈에서 잠긴 레벨 해금 시도 연결
- Lobby HUD 공용 재화 표시 및 실시간 갱신
- Lobby 해금 확인 팝업 (가격 / 보유 재화 표시, 재화 부족 시 확인 비활성화)

### feature(defense)

- Defense 레벨 뼈대 및 그리드 클래스 생성
- 그리드 BFS 경로 탐색 및 디버그 경로 표시
- 타워 배치 시 경로 재계산, 경로 차단 · 스폰/목표 · 적 위치를 막는 배치 거부
- 적 이동 · HP · 피격, 목표 도달 시 라이프 감소
- 타워 사거리 내 최근접 적 주기 공격
- 웨이브 스폰 및 진행, 승리 / 패배 판정
- 결과 화면 표시 및 일시정지, 로비 복귀
- DefenseEconomySubsystem 추가, 매치 결과를 공용 재화로 정산

### feature(ui)

- ActionButton 컴포넌트 (아이콘 / 텍스트 / 아이콘+텍스트 모드, GameplayTag + DataAsset 기반)
- Clicker HUD 파트 구조 (HUDRoot, Stats, PrimaryActions, DevButtons)

### fix

- UpgradeCost 오류 및 리빌드 오류 해결
- 에디터 설정 문제 해결
- UI-Economy 바인딩 크래시 해결
- 월드 재진입 시 GameInstance 참조 문제 해결 (SaveManager 참조 캐싱 시점 조정)
- 병합 과정에서 삭제된 GameplayTag 설정 복구
- 저장 데이터가 없을 때의 Clicker 로드 처리 수정
- 초기 해금 레벨이 기존 세이브에 항상 병합되도록 수정

### refactor

- Clicker 중심 구조를 Global 구조로 전환 (ClickerUISubsystem: GameInstance → World Subsystem)
- PlayerController 분리 (MyPlayerControllerBase + 레벨별 PlayerController)
- Global 서브시스템 로드를 GameMode BeginPlay에서 Initialize로 이동
- HUD 연결을 ClickerUISubsystem으로 이동, 오프라인 보상을 이벤트가 아닌 상태로 처리
- 클릭 VFX / 사운드를 ClickerTarget으로 이동 (ClickTargetActor → ClickerTarget)
- SaveManager 세이브 오브젝트 캐싱, 레벨 스냅샷을 GameplayTag 키로 범용화
- ActionButton과 ClickerUISubsystem 결합 해제
- 모듈 분리: HubCore + Lobby / Clicker / Defense (CoreRedirects로 기존 에셋 참조 유지)

### chore

- 직접 제작한 로직 에셋만 버전 관리하도록 정리
- 공용 Input Mapping Context로 통합 (IMC_Lobby → IMC_Default)
- 미사용 StarterContent 제거
- 프로젝트명 AMU로 변경 (프로젝트, 폴더, 저장소)

### docs

- 2026 Roadmap, Daily / Weekly 계획 문서 및 devlog 갱신
- README를 AMU 기준으로 재작성

## v0.1-core-stable (2025.09.06 ~ 2025.12.29)

### feature

- 오프라인 보상 수령 직후 즉시 저장 (예기치 못한 종료 시 중복 수령 방지)
- 오프라인 보상 누적 최대 8시간 제한
- FloatingText 풀 한도 초과 경고 추가

### fix

- CreateWidget 호출부 가드 추가로 크래시 예방
- 델리게이트 중복 구독으로 인한 ensure 에러 해결
- 델리게이트 매개변수 이름 중복으로 인한 빌드 오류 해결
- 시작 직후 오프라인 보상 UI가 표시되지 않는 문제 해결 (초기화 순서 조정)
- FloatingText / OfflineText 미표시 문제 해결
- 유령 캐시로 인한 Assertion 크래시 해결
- CreateLambda 관련 오류, WBP 오류 및 Toast UI 버그 해결

### refactor

- 소스 파일을 Public / Private, Gameplay / Systems / Data 기준으로 재분류하고 헤더 경로 정리
- EconomySnapshot 구조체를 별도 헤더로 분리
- UISubsystem의 EconomySubsystem 참조를 WeakPtr에서 ObjectPtr로 변경
- 틱 / 오프라인 재화 지급 플로우를 델리게이트 기반으로 변경
- 오브젝트 풀링 생성 방식 및 정책 통일, FloatingText 풀 재사용 구조 개선
- ToastWidgetBase 도입 및 토스트 위젯 상속 구조 정리
- OnOfflineReward 호출 구조 리팩터

### docs

- 문서 구조 세분화 (design / tech / planning / logs / testing)
- architecture_overview, system_ui, system_economy, api_reference 작성 및 갱신
- test_cases 작성, README 링크 수정
- Daily / Weekly 계획 문서 체계 도입

### chore

- 일지 자동 생성 스크립트 및 시작 프로그램 자동화
- dev 브랜치 생성 및 작업 브랜치 정리
