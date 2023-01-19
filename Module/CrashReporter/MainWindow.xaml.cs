using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace CrashReporter
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            var args = Environment.GetCommandLineArgs();
            Debug.Assert(args.Length == 3);

            LogPath = args[1];
            CallStack = args[2];

            this.DataContext = this;
            Loaded += OnLoaded;
        }

        private void Hyperlink_GitHubRepo(object sender, RequestNavigateEventArgs e)
        {
            System.Diagnostics.Process.Start("explorer.exe", e.Uri.AbsoluteUri);
            e.Handled = true;
        }

        private void OnLoaded(object sender, RoutedEventArgs e)
        {
            new System.Media.SoundPlayer("C:\\WINDOWS\\Media\\Windows Critical Stop.wav").Play();
        }

        public string LogPath { get; set; }
        public string CallStack { get; set; }
    }
}
