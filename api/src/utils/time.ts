export const getTimeDifference = (x: Date, y: Date) => {
    let diff =(x.getTime() - y.getTime()) / 1000;
    diff /= 60;
    return Math.abs(Math.round(diff));
}