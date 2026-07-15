# CLAUDE.md

이 저장소는 반도체 시료 생산주문관리 시스템 개인과제의 **PoC 3 (데이터 모니터링 Tool)** 입니다.

## 범위

- `data/samples.json`을 읽어 콘솔에 실시간으로 표시하는 것이 목적입니다.
- 데이터를 직접 수정하지 않습니다 (읽기 전용 도구). 데이터 변경은 DataPersistence /
  DummyDataGenerator PoC 몫입니다.
- 이 도구는 Windows(`conio.h`) 환경을 전제로 키 입력 감지를 구현했습니다.

## 규칙

- 매 갱신 주기마다 파일을 처음부터 다시 읽습니다 (증분/diff 갱신 아님) — PoC 범위에서는
  단순성이 우선입니다.
- JSON 파서는 DataPersistence PoC와 동일한 구현을 vendoring 했습니다 (namespace만
  `monitor::json`으로 조정). 스키마가 바뀌면 두 저장소 모두 갱신이 필요합니다.
