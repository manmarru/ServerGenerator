import tkinter as tk
import os

root = tk.Tk()
root.title("Server Generator")
root.geometry("300x380")

label = tk.Label(root, text = "Server Generator!")

# 헤더 사용 여부 체크박스
UsingHeader = tk.BooleanVar()
Header = tk.Checkbutton(root, text = "Use Header", variable = UsingHeader)

# 서버 접속 허용 인원 (0 = 무제한)
AccessLimit = tk.IntVar()
AccessLimit = tk.Entry(root, textvariable = AccessLimit)

# 콘솔에 출력할 정보 체크박스
# 1. 접속/접속해제 알림
# 2. 데이터 수신 정보
# 3. 데이터 전송 정보
label2 = tk.Label(root, text = "Console Output Options:")

AlertConnect = tk.BooleanVar()
AlertConnect = tk.Checkbutton(root, text = "Alert on Connect/Disconnect", variable = AlertConnect)

AlertReceive = tk.BooleanVar()
AlertReceive = tk.Checkbutton(root, text = "Alert on Data Receive", variable = AlertReceive)

AlertSend = tk.BooleanVar()
AlertSend = tk.Checkbutton(root, text = "Alert on Data Send", variable = AlertSend) 


# 세팅 저장/불러오기 버튼
SaveButton = tk.Button(root, text = "Save Settings")
LoadButton = tk.Button(root, text = "Load Settings")

# 서버 실행
StartButton = tk.Button(root, text = "Start Server")

# 위젯 배치
label.grid(row=0, column=0, columnspan=2, pady=15)
Header.grid(row=1, column=0, columnspan=2, pady=8)
AccessLimit.grid(row=2, column=0, columnspan=2, padx=20, pady=8)
label2.grid(row=3, column=0, columnspan=2, pady=12)
AlertConnect.grid(row=4, column=0, columnspan=2, sticky='w', padx=20, pady=2)
AlertReceive.grid(row=5, column=0, columnspan=2, sticky='w', padx=20, pady=2)
AlertSend.grid(row=6, column=0, columnspan=2, sticky='w', padx=20, pady=2)
StartButton.grid(row=8, column=0, columnspan=2, pady=(0, 20))
SaveButton.grid(row=7, column=1, padx=(5, 20), pady=20, sticky='w')
LoadButton.grid(row=7, column=0, padx=(20, 5), pady=20, sticky='e')

# 그리드 가운데 정렬
root.grid_columnconfigure(0, weight=1)
root.grid_columnconfigure(1, weight=1)

root.mainloop()