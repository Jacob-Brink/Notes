using System;
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

namespace BabbleSample
{
    /// Babble framework
    /// Starter code for CS212 Babble assignment
    public partial class MainWindow : Window
    {
        private string input;               // input file
        private List<String> words;             // input file broken into array of words
        private int wordCount = 500;        // number of words to babble
        private int order;

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
                words = Regex.Split(input, @"\s+").ToList();       // split into array of words
            }
        }

        private void analyzeInput(int order)
        {
            if (order > 0)
            {
                MessageBox.Show("Analyzing at order: " + order);
                this.order = order;
            }
        }

        private string GenerateKey(int start, int length)
        {
            List<String> keyList = words.GetRange(start, length);
            return keyList.Aggregate((elemLeft, elemRight) => elemLeft + " " + elemRight);
        }


        private void babbleButton_Click(object sender, RoutedEventArgs e)
        {

            textBlock1.Text = "";

            if (words.Count <= order)
            {
                textBlock1.Text += "Sample file is too small for order " + order;
                return;
            }

            Dictionary<string, List<string>> hashTable = new Dictionary<string, List<string>>();

            for (int i = 0; i < words.Count; i++)
            {

                if ((words.Count - i) > order)
                {
                    string key = GenerateKey(i, order);

                    if (!hashTable.ContainsKey(key))
                    {
                        hashTable.Add(key, new List<string>());
                    }

                    hashTable[key].Add(words[i + order]);

                }

            }

            List<string> keyWordList = words.GetRange(0, order);
        
            string keyValue = keyWordList.Aggregate((elemLeft, elemRight) => elemLeft + " " + elemRight);
            textBlock1.Text += keyValue + " ";
            Random random = new Random();

            for (int i = 0; i < wordCount; i++)
            {
                
                if (!hashTable.ContainsKey(keyValue))
                    break;

                List<string> nextWords = hashTable[keyValue];
                
                int randomIndex = random.Next(nextWords.Count);

                string nextWord = nextWords[randomIndex];

                textBlock1.Text += nextWord + " ";

                keyWordList.RemoveAt(0);
                keyWordList.Add(nextWord);

                keyValue = keyWordList.Aggregate((elemLeft, elemRight) => elemLeft + " " + elemRight);
            }
        }


        private void orderComboBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            analyzeInput(orderComboBox.SelectedIndex);
        }
    }
}
