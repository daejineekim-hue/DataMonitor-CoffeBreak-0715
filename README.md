# DataMonitor-CoffeBreak-0715

반도체 시료 생산주문관리 시스템의 **PoC 3: 데이터 모니터링 Tool**.

`DataPersistence` PoC와 동일한 포맷의 `data/samples.json`을 대상으로,
현재 저장된 데이터 상태를 콘솔에서 실시간으로 조회하는 관리자 도구입니다.

## 구조

```
include/json/JsonValue.h   # DataPersistence PoC와 동일한 JSON 파서/직렬화기 (namespace만 monitor::json으로 조정)
include/model/Sample.h     # 조회 전용 Sample 모델 (JSON -> 구조체 변환만 필요)
include/monitor/DataMonitor.h  # 주기적 재조회 + 렌더링 루프
src/main.cpp               # data/samples.json 을 대상으로 모니터 실행
```

## 동작 방식

- 지정한 간격(기본 2초)마다 `data/samples.json`을 다시 읽어 화면을 갱신합니다.
- 다른 프로세스(PoC2, PoC4 등)가 같은 파일을 수정하면 다음 갱신 주기에 반영됩니다.
- 화면에는 등록 시료 수, 총 재고, 시료별 재고 상태(여유/부족/고갈)를 표시합니다.
- `q` 키를 누르면 즉시 종료합니다 (Windows `conio.h` 기반).

## 빌드 및 실행

```powershell
./build.ps1
./build/data_monitor.exe
```

## 검증 방법

1. 별도 터미널에서 `DataPersistence` PoC(또는 `DummyDataGenerator` PoC)로
   `data/samples.json`에 데이터를 추가/수정
2. 이 도구가 몇 초 내로 화면을 자동 갱신하여 최신 상태를 반영하는지 확인
3. `q`로 정상 종료되는지 확인
