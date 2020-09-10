using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WpfApp1
{
    class Babbeler
    {

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
                    break;

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

            hashTable = new Dictionary<string, List<string>>();
            for (int i = 0; i < this.words.Count; i++)
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

        }

        public void load(List<string> words)
        {
            this.words = words;
            buildHash();
        }

        public string getAnalysis()
        {

            if (!canBabble())
                return "";

            string outputString = "";
            
            foreach (KeyValuePair<string, List<string>> entry in hashTable)
            {
                Dictionary<string, int> frequencyMap = new Dictionary<string, int>();
                outputString += entry.Key + " -> ";
                
                foreach (string value in entry.Value)
                {
                    if (!frequencyMap.ContainsKey(value))
                        frequencyMap.Add(value, 0);
                    frequencyMap[value] += 1;
                }

                
                foreach (KeyValuePair<string, int> wordEntry in frequencyMap)
                {
                    outputString += wordEntry.Key + " (" + wordEntry.Value + ") ,";
                }
                outputString += "\n";

            }

            return outputString;
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
