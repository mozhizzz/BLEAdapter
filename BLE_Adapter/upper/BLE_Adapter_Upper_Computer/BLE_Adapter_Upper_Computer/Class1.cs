using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace BLE_Adapter_Upper_Computer
{
    public class UartWindowClass
    {
        public static uint[] ChipUart = { 0, 0, 0, 0 };

        public void SearchUart(ComboBox Box)
        {
            string[] PortList = SerialPort.GetPortNames();
            SerialPort Com = new SerialPort();

            Box.Items.Clear();
            for (uint i = 0; i < PortList.Length; i++)
            {
                Box.Items.Add(PortList[i]);
            }
        }
        public bool ConnectCom(SerialPort UartPort, string PortName, string BaudRate, string Parity, string DataBits, string StopBits)
        {
            bool SuccessFlag = false;

            if (PortName == "")
            {
                MessageBox.Show("串口未选定");
                return SuccessFlag;
            }

            UartPort.PortName = PortName;
            UartPort.BaudRate = int.Parse(BaudRate);
            if (Parity == "None")
            {
                UartPort.Parity = System.IO.Ports.Parity.None;
            }
            else if (Parity == "Odd")
            {
                UartPort.Parity = System.IO.Ports.Parity.Odd;
            }
            else if (Parity == "Even")
            {
                UartPort.Parity = System.IO.Ports.Parity.Even;
            }
            else if (Parity == "Mark")
            {
                UartPort.Parity = System.IO.Ports.Parity.Mark;
            }
            else if (Parity == "Space")
            {
                UartPort.Parity = System.IO.Ports.Parity.Space;
            }
            UartPort.DataBits = int.Parse(DataBits);

            if (StopBits == "1")
            {
                UartPort.StopBits = System.IO.Ports.StopBits.One;
            }
            else if (StopBits == "1.5")
            {
                UartPort.StopBits = System.IO.Ports.StopBits.OnePointFive;
            }
            else if (StopBits == "2")
            {
                UartPort.StopBits = System.IO.Ports.StopBits.Two;
            }
            try
            {
                UartPort.Open();
                SuccessFlag = true;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
            return SuccessFlag;
        }
        public void CloseCom(SerialPort UartPort)
        {
            UartPort.Close();
        }
    }
}
