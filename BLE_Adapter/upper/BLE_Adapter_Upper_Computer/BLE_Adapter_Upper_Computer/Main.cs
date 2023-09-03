using System;
using System.Threading;
using System.Windows.Forms;

namespace BLE_Adapter_Upper_Computer
{
    public partial class Main : Form
    {
        private UartWindowClass Uart0 = new UartWindowClass();
        private AutoResetEvent RecvFinish = new AutoResetEvent(false);

        private delegate void TextBoxAdd(string Str);

        public Main()
        {
            InitializeComponent();
        }

        private void COM_select_comboBox_DropDown(object sender, EventArgs e)
        {
            ((ToolStripComboBox)sender).Text = null;
            Uart0.SearchUart(((ToolStripComboBox)sender));
        }

        private void toolStripComboBox1_DropDown(object sender, EventArgs e)
        {
            ((ToolStripComboBox)sender).Text = null;
            Uart0.SearchUart(((ToolStripComboBox)sender));
        }

        private void button1_Click(object sender, EventArgs e)
        {
            bool Flag = false;
            Flag = Uart0.ConnectCom(serialPort1, toolStripComboBox1.Text, toolStripComboBox2.Text, toolStripComboBox3.Text, toolStripComboBox4.Text, toolStripComboBox5.Text);
        }

        private void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            int offset = 0;
            byte[] buf = new byte[4096];
            do
            {
                offset += serialPort1.Read(buf, offset, serialPort1.BytesToRead);
            } while (serialPort1.BytesToRead != 0);

            SetStr(System.Text.Encoding.Default.GetString(buf));
            RecvFinish.Set();
        }

        private void SetStr(string Str)
        {
            if (this.textBox1.InvokeRequired)
            {
                TextBoxAdd d = new TextBoxAdd(SetStr);
                this.Invoke(d, new object[] { Str });
            }
            else
            {
                textBox1.Text = Str;
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            byte[] buf = System.Text.Encoding.Default.GetBytes(textBox1.Text);

            serialPort1.Write(textBox1.Text);
        }
    }
}
