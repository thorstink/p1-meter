```bash
docker run -it --rm -v /Users/thomashorstink/Projects/p1/p1-meter:/Users/thomashorstink/Projects/p1/p1-meter snowdreamtech/build-essential sh
docker run -d --rm -v /Users/thomashorstink/Projects/p1/p1-meter:/Users/thomashorstink/Projects/p1/p1-meter snowdreamtech/build-essential sh /Users/thomashorstink/Projects/p1/p1-meter/build.sh
```


export DIR=$pwd; docker run -t --rm -v $DIR:$DIR snowdreamtech/build-essential sh $DIR/build.sh
