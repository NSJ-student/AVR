using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;

namespace Temperature
{

    public partial class Form1 : Form
    {
        SerialPort Avr;
        Timer ConTimer;

        public Form1()
        {
            InitializeComponent();

            Avr = new SerialPort();
            //Avr.DataReceived += new SerialDataReceivedEventHandler(ReceiveHandler);
            SetSerial("COM10");

            // Serial 연결 대기 타이머
            ConTimer = new Timer();
            ConTimer.Interval = 1000;
            ConTimer.Tick += new EventHandler(GetSensor);

            cbInterval.SelectedIndex = 1;
            cbPort.SelectedIndex = 9;
            btnOpen.Enabled = true;
            btnClose.Enabled = false;
            btnGet.Enabled = false;
            btnStop.Enabled = false;
            cbInterval.Enabled = false;
            cbPort.Enabled = true;
        }

        private void ReceiveHandler(object sender, SerialDataReceivedEventArgs e)
        {
            SerialPort sp = sender as SerialPort;

            int i = 0;
            try
            {
                Avr.ReadTimeout = 100;
                int[] RxBuf = new int[16];  // 총 16 byte 수신예정
                int sum = 0;

                while ((RxBuf[0] = sp.ReadByte()) != '$') ;    // 맨 앞에 '$'가 올 때까지 수신
                sum = RxBuf[0];

                for (i = 1; i < 16; i++)
                {
                    RxBuf[i] = sp.ReadByte();  // 1byte 씩 수신
                    if (i < 14)
                    {
                        sum += RxBuf[i];        // 체크섬 계산
                    }
                }
                sum = (sum + 1) & (0xFF);         // 체크섬 계산

                if (sum == 0)                    // 체크섬 결과가 정확하면 온도값 출력
                {
                    byte[] RxBuf_b = new byte[16];
                    for (i = 0; i < 16; i++)
                    {
                        RxBuf_b[i] = (byte)RxBuf[i];
                    }
                    string Msg = Encoding.Default.GetString(RxBuf_b);
                    string Temp = Msg.Substring(6, 5);
                    string Unit = Msg.Substring(11, 1);
                    Update_Temp(Temp, Unit);
                }
                else                            // 체크섬 결과가 에러면 에러 출력
                {
                    Update_Temp("CS Fail", "?");
                }
            }
            catch(TimeoutException)
            {
                return;
            }
            catch (Exception ex)
            {
                GetStop();
                btnGet.Enabled = true;
                btnStop.Enabled = false;
                cbInterval.Enabled = true;
                lblStatus.Text = "수신 중 오류 발생 / " + ex.StackTrace.Substring(ex.StackTrace.Length - 7, 7).ToString();

                //MessageBox.Show(ex.Message + "\r\n" +ex.StackTrace.Substring(ex.StackTrace.Length - 7, 7).ToString() + " /" + i.ToString(), "에러", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
        public void SetSerial(string Port)
        {
            Avr.PortName = Port;
            Avr.BaudRate = 9600;
            Avr.DataBits = 8;
            Avr.Parity = Parity.None;
            Avr.StopBits = StopBits.One;
            Avr.Handshake = Handshake.None;
        }

        public void GetStart()
        {
            ConTimer.Start();
        }
        public void GetStop()
        {
            ConTimer.Stop();
        }
        public bool SetTimeInterval(int Interval)
        {
            try
            {
                ConTimer.Interval = Interval;
                return true;
            }
            catch
            {
                ConTimer.Interval = 1000;
                return false;
            }
        }
        private void GetSensor(object sender, EventArgs e)
        {
            int i = 0;
            try
            {
                Avr.Write("A");         // AVR에 신호 전송
                Avr.ReadTimeout = 500;

                int[] RxBuf = new int[16];  // 총 16 byte 수신예정
                int sum = 0;

                while ((RxBuf[0] = Avr.ReadByte()) != '$') ;    // 맨 앞에 '$'가 올 때까지 수신
                sum = RxBuf[0];

                for(i = 1; i<16; i++)
                {
                    RxBuf[i] = Avr.ReadByte();  // 1byte 씩 수신
                    if(i<14)
                    {
                        sum += RxBuf[i];        // 체크섬 계산
                    }
                }
                sum = (sum + 1)&(0xFF);         // 체크섬 계산
                

                if(sum == 0)                    // 체크섬 결과가 정확하면 온도값 출력
                {
                    byte[] RxBuf_b = new byte[16];
                    for (i = 0; i < 16; i++)
                    {
                        RxBuf_b[i] = (byte)RxBuf[i];
                    }
                    string Msg = Encoding.Default.GetString(RxBuf_b);
                    string Temp = Msg.Substring(6, 5);
                    string Unit = Msg.Substring(11, 1);
                    Update_Temp(Temp, Unit);
                }
                else                            // 체크섬 결과가 에러면 에러 출력
                {
                    Update_Temp("CS Fail", "?");
                }

            }
            catch(Exception ex)
            {
                GetStop();
                btnGet.Enabled = true;
                btnStop.Enabled = false;
                cbInterval.Enabled = true;
                lblStatus.Text = "신호 전송 중 오류 발생";

                //MessageBox.Show(ex.Message + "\r\n" +ex.StackTrace.Substring(ex.StackTrace.Length - 7, 7).ToString() + " /" + i.ToString(), "에러", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void Update_Temp(string strTemp, string Unit)
        {
            lblRxTemp.Text = strTemp;
            lblUnit.Text = Unit;
        }

        private void btnOpen_Click(object sender, EventArgs e)
        {
            if(cbPort.SelectedItem == null)
            {
                return;
            }
            if(Avr.IsOpen == true)
            {
                return;
            }

            SetSerial((string)cbPort.SelectedItem);
            Avr.Open();

            btnOpen.Enabled = false;
            btnClose.Enabled = true;
            btnGet.Enabled = true;
            btnStop.Enabled = false;
            cbInterval.Enabled = true;
            cbPort.Enabled = false;
            lblStatus.Text = "Serial Port Open";
        }
        private void btnClose_Click(object sender, EventArgs e)
        {
            if (Avr.IsOpen == false)
            {
                return;
            }

            GetStop();
            Avr.Close();

            btnOpen.Enabled = true;
            btnClose.Enabled = false;
            btnGet.Enabled = false;
            btnStop.Enabled = false;
            cbInterval.Enabled = false;
            cbPort.Enabled = true;
            lblStatus.Text = "Serial Port Closed";
        }

        private void btnGet_Click(object sender, EventArgs e)
        {
            if( false == SetTimeInterval(Convert.ToInt32((string)cbInterval.SelectedItem)))
            {
                cbInterval.SelectedIndex = 1;
            }
            GetStart();
            btnGet.Enabled = false;
            btnStop.Enabled = true;
            cbInterval.Enabled = false;
            lblStatus.Text = "온도값 수신 중...";
        }
        private void btnStop_Click(object sender, EventArgs e)
        {
            GetStop();
            btnGet.Enabled = true;
            btnStop.Enabled = false;
            cbInterval.Enabled = true;
            lblStatus.Text = "온도값 수신 중지";
        }
    }
}
