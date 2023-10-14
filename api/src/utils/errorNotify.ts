import io from '@pm2/io';

export default (title: string, error: any = {}) => {
  console.error(title, error);
  io.notifyError(title, {
    custom: {
      ...error,
    },
  });
};
