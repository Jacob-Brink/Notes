using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;

namespace WpfApp1
{
    class Babbeler
    {
        private int uniqueWordCount = 0;
        private int wordCount = 500;        // number of words to babble
        private int order = -1;
        private Dictionary<string, List<string>> hashTable = new Dictionary<string, List<string>>();
        private List<String> words;             // input file broken into array of words

        public Babbeler(int wordCount, int order)
        {
            this.wordCount = wordCount;
            this.order = order;
        }

        public string getBabel()
        {

            if (!canBabble())
                return "";

            string babel = "";

            List<string> keyWordList = words.GetRange(0, order);

            string keyValue = keyWordList.Aggregate((elemLeft, elemRight) => elemLeft + " " + elemRight);

            babel += keyValue + " ";

            Random random = new Random();

            for (int i = 0; i < wordCount; i++)
            {

                if (!hashTable.ContainsKey(keyValue))
                {
                    keyWordList = words.GetRange(0, order);
                    keyValue = keyWordList.Aggregate((elemLeft, elemRight) => elemLeft + " " + elemRight);
                            }

                List<string> nextWords = hashTable[keyValue];

                int randomIndex = random.Next(nextWords.Count);

                string nextWord = nextWords[randomIndex];

                babel += nextWord + " ";

                keyWordList.RemoveAt(0);
                keyWordList.Add(nextWord);

                keyValue = keyWordList.Aggregate((elemLeft, elemRight) => elemLeft + " " + elemRight);
            }

            return babel;

        }

        private void buildHash()
        {
            HashSet<string> uniqueWordSet = new HashSet<string>();
            hashTable = new Dictionary<string, List<string>>();

            for (int i = 0; i < this.words.Count; i++)
            {

                //check if key is within range
                if ((words.Count - i) > order)
                {

                    //generate a key
                    string key = GenerateKey(i, order);

                    //create new List for key if key not in dictionary
                    if (!hashTable.ContainsKey(key))
                        hashTable.Add(key, new List<string>());

                    //add word that follows words used to make key
                    hashTable[key].Add(words[i + order]);

                }

            }

            //set uniqueWordCount to uniqueWordSet
            uniqueWordCount = hashTable.Count + 1;

        }

        public int getUniqueWordCount() {
            return uniqueWordCount;
        }

        public void load(List<string> words)
        {
            this.words = words;
            buildHash();
        }

        public void getAnalysis(TextBlock text)
        {

            if (!canBabble())
                return;

            StringBuilder sb = new StringBuilder();

            sb.Append("Number of Unique Words (N order Sequences): " + uniqueWordCount + "\n");
            sb.Append("Total Number of Words: " + words.Count + "\n");


            foreach (KeyValuePair<string, List<string>> entry in hashTable)
            {
                sb.Append(entry.Key + " -> ");

                foreach (string value in entry.Value)
                {
                    sb.Append(value + ", ");
                }

                sb.Append("\n");

            }

            text.Text = sb.ToString();

        }

        private bool canBabble()
        {
            if (words == null)
                return false;

            if (order <= 0)
                return false;

            if (words.Count <= order)
                return false;

            return true;
        }

        public void setOrder(int order)
        {
            this.order = order;

            if (!canBabble())
                return;

            buildHash();
        }

        private string GenerateKey(int start, int length)
        {
            List<String> keyList = words.GetRange(start, length);
            return keyList.Aggregate((elemLeft, elemRight) => elemLeft + " " + elemRight);
        }
    }
}
