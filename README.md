# win_click_server
### 담당 : (데이터 처리 및 좌표계산) 박지수

### <클릭 프로세스>

1. 송신한 데이터(txt) 처리
    1-1. 프로그램 최초이용 초기 싱크 맞추기 - 각 모서리와 중앙 지점을 손으로 선텍하고 사진 상의 좌표값을 저장하고 상대 계산 데이터로 이용
    
        * setting.txt (4개의모서리 / 중앙 / x 위치 / y 위치)
        * setting_parsing()


2. 좌표계산
    2-1. 송신받은 데이터 처리 - text parsing (카메라 번호 / 시간 / x 위치 / y 위치)
          송신 받은 데이터 중 오차가 매우 큰 데이터 / 짧은 시간 내의 중복데이터 (동일 지점 두번 클릭인지 아닌지 판단) 제외 후 '유의미한 데이터'의 평균값을 구해 정확도를 높인다
          4대 카메라중 2대 이상의 카메라에서 터치를 인식해야 계산 가능
          
          * text_parsing(string filePath, int camera)
          
    2-2. 유의미한 데이터를 이용하여 삼각측량법으로 모니터 상의 터치할 좌표를 계산
    
          * calculate_x() / calculate_y()

3. 클릭
    3-1 클릭 실행
    
        * clickHaJa()
        * CLICK
    
main 소스코드    
https://github.com/Ascreen/win_click_server/blob/master/main.cpp
    
