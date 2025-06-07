import tkinter as tk
import tkinter.messagebox as messagebox
import tkinter.filedialog as filedialog
import os
import subprocess
import requests

# 세이브 함수
def save_settings():
    settings = {
        "UsingHeader": UsingHeader.get(),
        "AccessLimit": AccessLimitEntry.get(),
        "AlertConnect": AlertConnect.get(),
        "AlertReceive": AlertReceive.get(),
        "AlertSend": AlertSend.get(),
        "UserNameInput": UserNameInput.get()
    }
    
    file_path = filedialog.asksaveasfilename(
        defaultextension=".txt",
          filetypes=[("Text files", "*.txt")],
          initialdir=os.getcwd())
    if file_path:
        f = open(file_path, 'w')
        for key, value in settings.items():
            f.write(f"{key}={value}\n")
        f.close()

# 로드 함수
def load_settings():
    file_path = filedialog.askopenfilename(
        defaultextension=".txt",
          filetypes=[("Text files", "*.txt")],
          initialdir=os.getcwd())
        
    f = open(file_path, 'r')
    settings = {}
    for line in f:
        key, value = line.strip().split('=')
        settings[key] = value
            
    AccessLimitEntry.delete(0, tk.END)
    AccessLimitEntry.insert(0, settings.get("AccessLimit", "0"))
    UsingHeader.set(settings["UsingHeader"])
    AlertConnect.set(settings["AlertConnect"])
    AlertReceive.set(settings["AlertReceive"])
    UserNameInput.set(settings["UserNameInput"])
    AlertSend.set(settings["AlertSend"])
    f.close()

def GenerateServer():
    dir = os.path.dirname(os.path.abspath(__file__))
    exe_path = os.path.join(dir, "..", "Server", "x64", "Debug", "Server.exe")
    args = [
        exe_path,
        "AccessLimit", AccessLimitEntry.get(),
        "UsingHeader", str(UsingHeader.get()).lower(),
        "AlertConnect", str(AlertConnect.get()).lower(),
        "AlertReceive", str(AlertReceive.get()).lower(),
        "AlertSend", str(AlertSend.get()).lower(),
        "UserNameInput", str(UserNameInput.get()).lower()
    ]
    subprocess.Popen(args=args, creationflags=subprocess.CREATE_NEW_CONSOLE)
    print(requests.get("https://api.ipify.org").text)
    
import os
print("현재 작업 디렉토리:", os.getcwd())

root = tk.Tk()
root.title("Server Generator")
root.geometry("300x380")

label = tk.Label(root, text = "접속 가능 인원")

# 서버 접속 허용 인원 (0 = 무제한)
AccessLimit = tk.IntVar()
AccessLimitEntry = tk.Entry(root, textvariable = AccessLimit)

# 헤더 사용 여부 체크박스
UsingHeader = tk.BooleanVar()
Header = tk.Checkbutton(root, text = "헤더 데이터", variable = UsingHeader)

# 최초 데이터로 아이디 입력/서버가 번호 부여
UserNameInput = tk.BooleanVar()
UserNameInputButton = tk.Checkbutton(root, text = "아이디 입력받음", variable = UserNameInput)

# 콘솔에 출력할 정보 체크박스
# 1. 접속/접속해제 알림
# 2. 데이터 수신 정보
# 3. 데이터 전송 정보
label2 = tk.Label(root, text = "콘솔에 출력할 정보:")

AlertConnect = tk.BooleanVar()
AlertReceive = tk.BooleanVar()
AlertSend = tk.BooleanVar()
AlertConnectButton = tk.Checkbutton(root, text = "접속/해제 시 알림", variable = AlertConnect)
AlertReceiveButton = tk.Checkbutton(root, text = "데이터 수신 알림", variable = AlertReceive)
AlertSendButton = tk.Checkbutton(root, text = "데이터 송신 알림", variable = AlertSend) 

# 세팅 저장/불러오기 버튼
SaveButton = tk.Button(root, text = "Save", command = save_settings)
LoadButton = tk.Button(root, text = "Load", command = load_settings)

# 서버 실행
StartButton = tk.Button(root, text = "서버 생성", command = GenerateServer)

# 위젯 배치
label.grid(row=0, column=0, columnspan=2, pady=5)
AccessLimitEntry.grid(row=1, column=0, columnspan=2, padx=20, pady=5)
Header.grid(row=2, column=0, columnspan=2, pady=8)
label2.grid(row=3, column=0, columnspan=2, pady=12)

AlertConnectButton.grid(row=4, column=0, sticky='ew', padx=20, pady=2)
AlertReceiveButton.grid(row=5, column=0, sticky='ew', padx=20, pady=2)
AlertSendButton.grid(row=4, column=1, sticky='ew', padx=20, pady=2)
UserNameInputButton.grid(row=5, column=1, sticky='ew', padx=20, pady=2)

SaveButton.grid(row=8, column=0, padx=(20, 5), pady=20, sticky='e')
LoadButton.grid(row=8, column=1, padx=(5, 20), pady=20, sticky='w')
StartButton.grid(row=9, column=0, columnspan=2, pady=(0, 20))

# 그리드 가운데 정렬
root.grid_columnconfigure(0, weight=1)
root.grid_columnconfigure(1, weight=1)

root.mainloop()




