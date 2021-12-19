# 3ds-brew


## Building code

```sh
> docker build -f 3ds.dockerfile -t 3dsbrew .
```

## Upload to 3ds

1. Run Build code (see above)
2. Run the upload:

```sh
> docker run -e ADDRESS=<address-of-3ds> 3dsbrew
```

