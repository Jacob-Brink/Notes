
﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.IO;
using System.Collections;
using System.Windows.Documents;
using WpfApp1;

namespace BabbleSample
{
    /// Babble framework
    /// Starter code for CS212 Babble assignment
    public partial class MainWindow : Window
    {
        private string input;               // input file
        private Dictionary<string, List<string>> hashTable = new Dictionary<string, List<string>>();
        Babbeler babbeler = new Babbeler(200, 1);

        public MainWindow()
        {
            InitializeComponent();
        }

        private void loadButton_Click(object sender, RoutedEventArgs e)
        {
            Microsoft.Win32.OpenFileDialog ofd = new Microsoft.Win32.OpenFileDialog();
            ofd.FileName = "Sample"; // Default file name
            ofd.DefaultExt = ".txt"; // Default file extension
            ofd.Filter = "Text documents (.txt)|*.txt"; // Filter files by extension

            // Show open file dialog box
            if ((bool)ofd.ShowDialog())
            {
                textBlock1.Text = "Loading file " + ofd.FileName + "\n";
                input = System.IO.File.ReadAllText(ofd.FileName);  // read file
                babbeler.load(Regex.Split(input, @"\s+").ToList());
                outputAnalysis();
            }
        }
        
        private void outputAnalysis()
        {
            if (textBlock1 == null) //because orderComboBox_SelectionChanged runs before window loads
                return;
            textBlock1.Text = babbeler.getAnalysis();
        }


        private void analyzeInput(int order)
        {
            babbeler.setOrder(order);
            MessageBox.Show("Analyzing at order: " + order);
            outputAnalysis();
        }
        
        private void babbleButton_Click(object sender, RoutedEventArgs e)
        {
            textBlock1.Text = babbeler.getBabel();               
        }


        private void orderComboBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            analyzeInput(orderComboBox.SelectedIndex+1);
        }
    }
}