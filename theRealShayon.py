import twitter
import subprocess
import time

# get twitter login
credential_file = open('credentials.txt', 'r')
credentials = credential_file.readlines()

CONSUMER_KEY = credentials[0].strip()
CONSUMER_SECRET = credentials[1].strip()
ACCESS_TOKEN = credentials[2].strip()
ACCESS_TOKEN_SECRET = credentials[3].strip()

tweet = twitter.Api(consumer_key=CONSUMER_KEY, consumer_secret=CONSUMER_SECRET,
                    access_token_key=ACCESS_TOKEN, access_token_secret=ACCESS_TOKEN_SECRET)

# get delay time
delay_input = input("Tweet Delay (mins): ")
delay = int(delay_input) * 60
# print(delay)

while (True):
    # run c++ program to get generated sentence
    print("--C++ OUTPUT--")
    subprocess.call("./main")
    print("\n--PYTHON SCRIPT--")

    # read generated sentence from file
    input_file = open('output.txt', 'r')
    generated_sentence = input_file.read()
    print("Tweet: " + generated_sentence)

    # check if generated sentence has already been tweeted
    statuses = tweet.GetUserTimeline(screen_name="theRealShayon")
    isGoodTweet = False
    for s in statuses:
        if (s.text == generated_sentence):
            print("Tweet has already been tweeted")
            isGoodTweet = False
            break
        isGoodTweet = True

    # if not tweet it and wait, else generate a new sentence with no delay
    if (isGoodTweet):
        tweet.PostUpdate(generated_sentence)
        print("\nTweet Tweeted.\n")
        time.sleep(delay)
