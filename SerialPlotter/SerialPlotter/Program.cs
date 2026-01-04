using System;
using System.Windows.Forms;

namespace SerialPlotter
{
    static class Program
    {
        /// <summary>
        /// アプリケーションのメインエントリポイント
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new MainForm());
        }
    }
}

