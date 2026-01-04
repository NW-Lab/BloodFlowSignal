using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Windows.Forms;
using ScottPlot;
using ScottPlot.WinForms;

namespace SerialPlotter
{
    public partial class MainForm : Form
    {
        private FormsPlot plotControl;
        private ComboBox comboBoxPorts;
        private ComboBox comboBoxBaudRate;
        private Button buttonConnect;
        private Button buttonDisconnect;
        private Button buttonClear;
        private System.Windows.Forms.Label labelStatus;
        private SerialPort serialPort;
        private List<double> dataPoints;
        private int maxDataPoints = 1000;
        private System.Windows.Forms.Timer updateTimer;

        public MainForm()
        {
            InitializeComponent();
            dataPoints = new List<double>();
            serialPort = new SerialPort();
            serialPort.DataReceived += SerialPort_DataReceived;
            
            updateTimer = new System.Windows.Forms.Timer();
            updateTimer.Interval = 50; // 50ms更新間隔
            updateTimer.Tick += UpdateTimer_Tick;
        }

        private void InitializeComponent()
        {
            this.Text = "Serial Plotter - 血流計測";
            this.Size = new Size(1000, 700);
            this.StartPosition = FormStartPosition.CenterScreen;

            // コントロールパネル
            Panel controlPanel = new Panel
            {
                Dock = DockStyle.Top,
                Height = 80,
                BackColor = System.Drawing.Color.LightGray
            };

            // COMポート選択
            System.Windows.Forms.Label labelPort = new System.Windows.Forms.Label
            {
                Text = "COMポート:",
                Location = new Point(10, 15),
                AutoSize = true
            };

            comboBoxPorts = new ComboBox
            {
                Location = new Point(100, 12),
                Width = 120,
                DropDownStyle = ComboBoxStyle.DropDownList
            };
            RefreshPorts();

            Button buttonRefresh = new Button
            {
                Text = "更新",
                Location = new Point(230, 10),
                Width = 60
            };
            buttonRefresh.Click += (s, e) => RefreshPorts();

            // ボーレート選択
            System.Windows.Forms.Label labelBaudRate = new System.Windows.Forms.Label
            {
                Text = "ボーレート:",
                Location = new Point(300, 15),
                AutoSize = true
            };

            comboBoxBaudRate = new ComboBox
            {
                Location = new Point(390, 12),
                Width = 100,
                DropDownStyle = ComboBoxStyle.DropDownList
            };
            comboBoxBaudRate.Items.AddRange(new object[] { 
                "9600", "19200", "38400", "57600", "115200", "230400", "460800", "921600" 
            });
            comboBoxBaudRate.SelectedIndex = 4; // 115200をデフォルト

            // 接続ボタン
            buttonConnect = new Button
            {
                Text = "接続",
                Location = new Point(500, 10),
                Width = 80
            };
            buttonConnect.Click += ButtonConnect_Click;

            buttonDisconnect = new Button
            {
                Text = "切断",
                Location = new Point(590, 10),
                Width = 80,
                Enabled = false
            };
            buttonDisconnect.Click += ButtonDisconnect_Click;

            buttonClear = new Button
            {
                Text = "クリア",
                Location = new Point(680, 10),
                Width = 80
            };
            buttonClear.Click += ButtonClear_Click;

            // ステータスラベル
            labelStatus = new System.Windows.Forms.Label
            {
                Text = "未接続",
                Location = new Point(10, 50),
                AutoSize = true,
                ForeColor = System.Drawing.Color.Red,
                Font = new Font(this.Font.FontFamily, 10, System.Drawing.FontStyle.Bold)
            };

            controlPanel.Controls.Add(labelPort);
            controlPanel.Controls.Add(comboBoxPorts);
            controlPanel.Controls.Add(buttonRefresh);
            controlPanel.Controls.Add(labelBaudRate);
            controlPanel.Controls.Add(comboBoxBaudRate);
            controlPanel.Controls.Add(buttonConnect);
            controlPanel.Controls.Add(buttonDisconnect);
            controlPanel.Controls.Add(buttonClear);
            controlPanel.Controls.Add(labelStatus);

            // プロットコントロール
            plotControl = new FormsPlot
            {
                Dock = DockStyle.Fill
            };
            
            InitializePlot();

            this.Controls.Add(plotControl);
            this.Controls.Add(controlPanel);

            this.FormClosing += MainForm_FormClosing;
        }

        private void InitializePlot()
        {
            plotControl.Plot.Clear();
            plotControl.Plot.Title("血流データ");
            plotControl.Plot.XLabel("サンプル数");
            plotControl.Plot.YLabel("値");
            plotControl.Plot.Axes.AutoScale();
            plotControl.Refresh();
        }

        private void RefreshPorts()
        {
            comboBoxPorts.Items.Clear();
            string[] ports = SerialPort.GetPortNames();
            if (ports.Length > 0)
            {
                comboBoxPorts.Items.AddRange(ports);
                comboBoxPorts.SelectedIndex = 0;
            }
            else
            {
                MessageBox.Show("利用可能なCOMポートが見つかりません。", "エラー", 
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }

        private void ButtonConnect_Click(object? sender, EventArgs e)
        {
            if (comboBoxPorts.SelectedItem == null)
            {
                MessageBox.Show("COMポートを選択してください。", "エラー", 
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }

            try
            {
                serialPort.PortName = comboBoxPorts.SelectedItem.ToString() ?? "COM1";
                serialPort.BaudRate = int.Parse(comboBoxBaudRate.SelectedItem?.ToString() ?? "115200");
                serialPort.DataBits = 8;
                serialPort.Parity = Parity.None;
                serialPort.StopBits = StopBits.One;
                serialPort.Handshake = Handshake.None;
                serialPort.ReadTimeout = 500;
                serialPort.WriteTimeout = 500;

                serialPort.Open();
                
                buttonConnect.Enabled = false;
                buttonDisconnect.Enabled = true;
                comboBoxPorts.Enabled = false;
                comboBoxBaudRate.Enabled = false;
                
                labelStatus.Text = $"接続中: {serialPort.PortName} @ {serialPort.BaudRate}bps";
                labelStatus.ForeColor = System.Drawing.Color.Green;

                updateTimer.Start();
            }
            catch (Exception ex)
            {
                MessageBox.Show($"接続エラー: {ex.Message}", "エラー", 
                    MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void ButtonDisconnect_Click(object? sender, EventArgs e)
        {
            DisconnectSerial();
        }

        private void DisconnectSerial()
        {
            try
            {
                updateTimer.Stop();
                
                if (serialPort.IsOpen)
                {
                    serialPort.Close();
                }

                buttonConnect.Enabled = true;
                buttonDisconnect.Enabled = false;
                comboBoxPorts.Enabled = true;
                comboBoxBaudRate.Enabled = true;
                
                labelStatus.Text = "未接続";
                labelStatus.ForeColor = System.Drawing.Color.Red;
            }
            catch (Exception ex)
            {
                MessageBox.Show($"切断エラー: {ex.Message}", "エラー", 
                    MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void ButtonClear_Click(object? sender, EventArgs e)
        {
            lock (dataPoints)
            {
                dataPoints.Clear();
            }
            UpdatePlot();
        }

        private void SerialPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            try
            {
                string data = serialPort.ReadLine().Trim();
                
                if (double.TryParse(data, out double value))
                {
                    lock (dataPoints)
                    {
                        dataPoints.Add(value);
                        
                        // 最大データポイント数を超えたら古いデータを削除
                        if (dataPoints.Count > maxDataPoints)
                        {
                            dataPoints.RemoveAt(0);
                        }
                    }
                }
            }
            catch (Exception)
            {
                // データ読み取りエラーは無視（タイムアウトなど）
            }
        }

        private void UpdateTimer_Tick(object? sender, EventArgs e)
        {
            UpdatePlot();
        }

        private void UpdatePlot()
        {
            if (this.InvokeRequired)
            {
                this.Invoke(new Action(UpdatePlot));
                return;
            }

            lock (dataPoints)
            {
                if (dataPoints.Count > 0)
                {
                    plotControl.Plot.Clear();
                    
                    double[] yData = dataPoints.ToArray();
                    double[] xData = Enumerable.Range(0, yData.Length).Select(i => (double)i).ToArray();
                    
                    var scatter = plotControl.Plot.Add.Scatter(xData, yData);
                    scatter.LineWidth = 2;
                    scatter.Color = ScottPlot.Color.FromHex("#0066CC");
                    
                    plotControl.Plot.Title("血流データ");
                    plotControl.Plot.XLabel("サンプル数");
                    plotControl.Plot.YLabel("値");
                    plotControl.Plot.Axes.AutoScale();
                    
                    plotControl.Refresh();
                }
            }
        }

        private void MainForm_FormClosing(object? sender, FormClosingEventArgs e)
        {
            DisconnectSerial();
            serialPort.Dispose();
            updateTimer.Dispose();
        }
    }
}
